#include "stockermodifydialog.h"
#include "ui_stockermodifydialog.h"
#include <QtSql>
#include <QMessageBox>

StockerModifyDialog::StockerModifyDialog(const QString& m_id,
                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockerModifyDialog)
{
    ui->setupUi(this);

    this->m_id = m_id;

    QSqlQuery query;
    query.prepare("SELECT name, code, price, number, expiration, dosage "
                  "FROM medicine WHERE id = :id");
    query.bindValue(":id", m_id);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误18", query.lastError().text());
        return;
    }
    while(query.next()) {
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        QString price = query.value(2).toString();
        QString number = query.value(3).toString();
        QDate expiration = query.value(4).toDate();
        QString dosage = query.value(5).toString();

        ui->lineEdit_1->setText(name);
        ui->lineEdit_2->setText(code);
        ui->doubleSpinBox->setValue(price.toDouble());
        ui->spinBox->setValue(number.toInt());
        ui->dateEdit->setDate(expiration);
        ui->lineEdit_6->setText(dosage);
    }
}

StockerModifyDialog::~StockerModifyDialog()
{
    delete ui;
}

void StockerModifyDialog::accept()
{
    if(ui->lineEdit_1->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::critical(this, "必填项为空", "必填项不能为空");
        return;
    }

    QString name = ui->lineEdit_1->text();
    QString code = ui->lineEdit_2->text();
    QString price = QString::number(ui->doubleSpinBox->value());
    QString number = QString::number(ui->spinBox->value());
    QString expiration = ui->dateEdit->date().toString(Qt::DateFormat::ISODate);
    QString dosage = ui->lineEdit_6->text();

    QSqlQuery query;
    QString sql = QString("UPDATE medicine "
                          "SET name = '%1', "
                          "code = '%2', "
                          "price = %3, "
                          "number = %4, "
                          "expiration = '%5', "
                          "dosage = '%6' "
                          "WHERE id = %7").arg(name,
                                               code,
                                               price,
                                               number,
                                               expiration,
                                               dosage,
                                               m_id);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误19", query.lastError().text());
        return;
    }
    QDialog::accept();
}
