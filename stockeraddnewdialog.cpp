#include "stockeraddnewdialog.h"
#include "ui_stockeraddnewdialog.h"
#include <QtSql>
#include <QMessageBox>

StockerAddNewDialog::StockerAddNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockerAddNewDialog)
{
    ui->setupUi(this);
}

StockerAddNewDialog::~StockerAddNewDialog()
{
    delete ui;
}

void StockerAddNewDialog::accept()
{
    if(ui->lineEdit_1->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::critical(this, "错误", "未填写必填项");
        return;
    }

    code = ui->lineEdit_1->text();
    name = ui->lineEdit_2->text();
    price = QString::number(ui->doubleSpinBox->value());
    number = QString::number(ui->spinBox->value());
    expiration = ui->dateEdit->date().toString(Qt::DateFormat::ISODate);
    dosage = ui->lineEdit_3->text();

    QDialog::accept();
}
