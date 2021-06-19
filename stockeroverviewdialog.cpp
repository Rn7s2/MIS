#include "stockeroverviewdialog.h"
#include "ui_stockeroverviewdialog.h"
#include "stockermedicinedetaildialog.h"
#include <QtSql>
#include <QMessageBox>

StockerOverViewDialog::StockerOverViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockerOverViewDialog)
{
    ui->setupUi(this);
    ui->tableWidget_1->setColumnCount(7);

    QStringList head;
    head.append("序号");
    head.append("名称");
    head.append("条码");
    head.append("数量");
    head.append("价格");
    head.append("保质期");
    head.append("用法用量");
    ui->tableWidget_1->setHorizontalHeaderLabels(head);
    ui->tableWidget_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery query;
    if(!query.exec("SELECT * FROM medicine;")) {
        QMessageBox::critical(this, "数据库错误17", query.lastError().text());
        return;
    }
    int cnt = 0;
    while(query.next()) {
        QString id = query.value(0).toString();
        QString code = query.value(1).toString();
        QString name = query.value(2).toString();
        QString price = query.value(3).toString();
        QString number = query.value(4).toString();
        QString expiration = query.value(5).toString();
        QString dosage = query.value(6).toString();

        QTableWidgetItem* a = new QTableWidgetItem(id);
        QTableWidgetItem* b = new QTableWidgetItem(name);
        QTableWidgetItem* c = new QTableWidgetItem(code);
        QTableWidgetItem* d = new QTableWidgetItem(number);
        QTableWidgetItem* e = new QTableWidgetItem(price);
        QTableWidgetItem* f = new QTableWidgetItem(expiration);
        QTableWidgetItem* g = new QTableWidgetItem(dosage);

        QDate date = query.value(5).toDate();
        if(QDate::currentDate().daysTo(date) <= 60)
            f->setBackgroundColor(Qt::GlobalColor::green);

        if(number.toInt() <= 2)
            d->setBackgroundColor(Qt::GlobalColor::blue);

        ui->tableWidget_1->insertRow(cnt);
        ui->tableWidget_1->setItem(cnt, 0, a);
        ui->tableWidget_1->setItem(cnt, 1, b);
        ui->tableWidget_1->setItem(cnt, 2, c);
        ui->tableWidget_1->setItem(cnt, 3, d);
        ui->tableWidget_1->setItem(cnt, 4, e);
        ui->tableWidget_1->setItem(cnt, 5, f);
        ui->tableWidget_1->setItem(cnt, 6, g);
        ++cnt;
    }
    ui->lineEdit->setText(QString::number(cnt));
}

StockerOverViewDialog::~StockerOverViewDialog()
{
    delete ui;
}

void StockerOverViewDialog::on_tableWidget_1_itemDoubleClicked(QTableWidgetItem *item)
{
    QString id = ui->tableWidget_1->item(item->row(), 0)->text();
    StockerMedicineDetailDialog d(id, this);
    d.exec();
}
