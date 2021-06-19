#include "doctorviewprescriptiondialog.h"
#include "doctormodifyprescriptiondialog.h"
#include "ui_doctorviewprescriptiondialog.h"
#include <QtSql>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>

DoctorViewPrescriptionDialog::DoctorViewPrescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoctorViewPrescriptionDialog)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    QStringList head;
    head.append("流水号");
    head.append("病人");
    head.append("开单日期");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    disableButtons();
    FuzzySearchPrescription("");
}

void DoctorViewPrescriptionDialog::makeDocument()
{
    this->repaint(QRect(ui->widget->x(),
                        ui->widget->y(),
                        ui->widget->width(),
                        ui->widget->height()));
}

QPixmap DoctorViewPrescriptionDialog::makePixmap()
{
    QFont font;
    font.setPointSize(34);

    QPixmap pix("pic.jpg");

    QPainter painter(&pix);
    painter.setFont(font);

    painter.drawText(QRect(330, 305, 230, 80), lst[2]);
    painter.drawText(QRect(735, 305, 230, 80), lst[4]);
    painter.drawText(QRect(1050, 305, 230, 80), lst[3]);
    painter.drawText(QRect(330, 480, 230, 80), lst[0]);
    painter.drawText(QRect(930, 480, 230, 80), lst[1].mid(0, 4));
    painter.drawText(QRect(1100, 480, 230, 80), lst[1].mid(5, 2));
    painter.drawText(QRect(1225, 480, 230, 80), lst[1].mid(8, 2));
    painter.drawText(QRect(350, 575, 1000, 80), lst[5]);

    QSqlQuery query;
    QString medicine_table = "p_" + lst[0];
    QString sql = QString("SELECT medicine_id, number FROM %1").arg(medicine_table);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误89", query.lastError().text());
        return QPixmap();
    }

    int y = 850;
    double total_price = 0;
    while(query.next()) {
        QSqlQuery q;
        sql = "SELECT name, price, dosage FROM medicine WHERE id = " + query.value(0).toString();
        if(!q.exec(sql)) {
            QMessageBox::critical(this, "数据库错误34", query.lastError().text());
            return QPixmap();
        }
        q.next();
        QString number = query.value(1).toString();
        QString name = q.value(0).toString();
        QString price = q.value(1).toString();
        QString dosage = q.value(2).toString();
        total_price += number.toDouble() * price.toDouble();

        painter.drawText(QRect(350, y, 1000, 80), name + " x" + number);
        y += 60;
        painter.drawText(QRect(350, y, 1000, 80), "    " + dosage);
        y += 80;
    }

    painter.drawText(QRect(460, 1890, 230, 80), QString::number(total_price) + " 元");

    return pix;
}

void DoctorViewPrescriptionDialog::enableButtons()
{
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}

void DoctorViewPrescriptionDialog::disableButtons()
{
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void DoctorViewPrescriptionDialog::FuzzySearchPrescription(const QString &str)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    QSqlQuery query;
    QString sql;
    if(str == QString())
        sql = "SELECT id, patient, date FROM prescription";
    else
        sql = QString("SELECT id, patient, date FROM prescription "
                      "WHERE patient LIKE '%%%1%%'").arg(str);

    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误26", query.lastError().text());
        return;
    }

    int cnt = 0;
    while(query.next()) {
        QString id = query.value(0).toString();
        QString patient = query.value(1).toString();
        QString date = query.value(2).toString();

        ui->tableWidget->insertRow(cnt);
        ui->tableWidget->setItem(cnt, 0, new QTableWidgetItem(id));
        ui->tableWidget->setItem(cnt, 1, new QTableWidgetItem(patient));
        ui->tableWidget->setItem(cnt, 2, new QTableWidgetItem(date));
        ++cnt;
    }
}

DoctorViewPrescriptionDialog::~DoctorViewPrescriptionDialog()
{
    delete ui;
}

void DoctorViewPrescriptionDialog::on_lineEdit_textChanged(const QString &str)
{
    FuzzySearchPrescription(str);
}

void DoctorViewPrescriptionDialog::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if(current != nullptr && previous != nullptr && current->row() == previous->row())
        return;
    makeDocument();
    disableButtons();
    if(current == nullptr)
        return;
    enableButtons();
    QString p_id = ui->tableWidget->item(current->row(), 0)->text();
    QSqlQuery query;
    QString sql = "SELECT * FROM prescription WHERE "
                  "id = ";
    sql += p_id;
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误27", query.lastError().text());
        return;
    }
    query.next();
    QString id = query.value(0).toString();
    QString date = query.value(2).toString();
    QString patient = query.value(3).toString();
    QString age = query.value(4).toString();
    QString sex = query.value(5).toString();
    QString diagnosis = query.value(6).toString();

    if(sex == "0")
        sex = "男";
    else
        sex = "女";

    lst.clear();
    lst.append(id);
    lst.append(date);
    lst.append(patient);
    lst.append(age);
    lst.append(sex);
    lst.append(diagnosis);

    makeDocument();
}

void DoctorViewPrescriptionDialog::paintEvent(QPaintEvent *event)
{
    if(ui->tableWidget->selectedItems().size() != 0) {
        QPixmap pix(makePixmap());

        QRect rect(ui->widget->x(),
                   ui->widget->y(),
                   ui->widget->width(),
                   ui->widget->height());
        QPainter p(this);
        p.drawPixmap(rect, pix, pix.rect());
    }
    QDialog::paintEvent(event);
}

void DoctorViewPrescriptionDialog::on_pushButton_1_clicked()
{
    QPrinter printer;
    printer.setPageSize(QPrinter::A5);
    printer.setFullPage(true);
    QPrintDialog dlg(&printer, this);
    if(dlg.exec() == QDialog::Accepted) {
        QPixmap pix(makePixmap());
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = pix.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(),
                            size.width(), size.height());
        painter.setWindow(pix.rect());
        painter.drawImage(0, 0, pix.toImage());
    }
}

void DoctorViewPrescriptionDialog::on_pushButton_2_clicked()
{
    DoctorModifyPrescriptionDialog dialog(lst, this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    if(dialog.exec() != QDialog::Accepted)
        return;

    QSqlQuery query;
    QString sql = "SELECT * FROM prescription WHERE "
                  "id = ";
    sql += lst[0];
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误35", query.lastError().text());
        return;
    }
    query.next();
    QString id = query.value(0).toString();
    QString date = query.value(2).toString();
    QString patient = query.value(3).toString();
    QString age = query.value(4).toString();
    QString sex = query.value(5).toString();
    QString diagnosis = query.value(6).toString();

    if(sex == "0")
        sex = "男";
    else
        sex = "女";

    lst.clear();
    lst.append(id);
    lst.append(date);
    lst.append(patient);
    lst.append(age);
    lst.append(sex);
    lst.append(diagnosis);

    makeDocument();
}

void DoctorViewPrescriptionDialog::on_pushButton_3_clicked()
{
    // 删除操作需要什么？
    // 删除p_xxx即处方对应的药品表
    // 删除prescription中对应的条目
    // 从控件中删除项目。

    if(QMessageBox::warning(this, "危险操作", "确定删除吗？", QMessageBox::Ok | QMessageBox::Cancel) != QMessageBox::Ok)
        return;
    QString p_id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
    QString medicine_table = "p_" + p_id;
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    QSqlQuery query;
    if(!query.exec("DROP TABLE " + medicine_table)) {
        QMessageBox::critical(this, "数据库错误29", query.lastError().text());
        return;
    }
    if(!query.exec("DELETE FROM prescription WHERE id = " + p_id)) {
        QMessageBox::critical(this, "数据库错误30", query.lastError().text());
        return;
    }
}
