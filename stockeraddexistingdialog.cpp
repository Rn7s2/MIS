#include "stockeraddexistingdialog.h"
#include "ui_stockeraddexistingdialog.h"

StockerAddExistingDialog::StockerAddExistingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockerAddExistingDialog)
{
    ui->setupUi(this);
    num = 1;
}

StockerAddExistingDialog::~StockerAddExistingDialog()
{
    delete ui;
}

void StockerAddExistingDialog::accept()
{
    num = ui->spinBox->value();
    QDialog::accept();
}
