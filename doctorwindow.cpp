#include "doctorwindow.h"
#include "ui_doctorwindow.h"
#include "doctornewprescriptiondialog.h"
#include "doctorviewprescriptiondialog.h"

DoctorWindow::DoctorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorWindow)
{
    ui->setupUi(this);
}

DoctorWindow::~DoctorWindow()
{
    delete ui;
}

// 开具处方
void DoctorWindow::on_pushButton_1_clicked()
{
    DoctorNewPrescriptionDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    dialog.exec();
}

// 查看处方
void DoctorWindow::on_pushButton_2_clicked()
{
    DoctorViewPrescriptionDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    dialog.exec();
}
