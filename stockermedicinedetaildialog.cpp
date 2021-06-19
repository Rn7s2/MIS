#include "stockermedicinedetaildialog.h"
#include "ui_stockermedicinedetaildialog.h"
#include "stockrecordviewdialog.h"
#include <QtSql>
#include <QMessageBox>

StockerMedicineDetailDialog::StockerMedicineDetailDialog(const QString& m_id,
                                                         QWidget *parent) :
    QDialog(parent), ui(new Ui::StockerMedicineDetailDialog)
{
    ui->setupUi(this);

    this->m_id = m_id;

    QSqlQuery query;
    query.prepare("SELECT name, code, price, number, expiration, dosage "
               "FROM medicine WHERE id = :id");
    query.bindValue(":id", m_id);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误9", query.lastError().text());
        return;
    }
    while(query.next()) {
        QString name = query.value(0).toString();
        QString code = query.value(1).toString();
        QString price = query.value(2).toString();
        QString number = query.value(3).toString();
        QString expiration = query.value(4).toString();
        QString dosage = query.value(5).toString();

        ui->lineEdit_1->setText(name);
        ui->lineEdit_2->setText(code);
        ui->lineEdit_3->setText(price);
        ui->lineEdit_4->setText(number);
        ui->lineEdit_5->setText(expiration);
        ui->lineEdit_6->setText(dosage);
    }
}

StockerMedicineDetailDialog::~StockerMedicineDetailDialog()
{
    delete ui;
}

void StockerMedicineDetailDialog::on_pushButton_2_clicked()
{
    StockRecordViewDialog dialog(m_id, this);
    dialog.exec();
}

