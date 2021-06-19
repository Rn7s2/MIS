#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(const int& usertype, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    type = usertype;
    ui->comboBox->setCurrentIndex(type);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_comboBox_currentIndexChanged(int index)
{
    type = index;
}

