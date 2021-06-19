#include "stockoutconfirmdialog.h"
#include "ui_stockoutconfirmdialog.h"
#include <QtSql>
#include <QMessageBox>

StockOutConfirmDialog::StockOutConfirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockOutConfirmDialog)
{
    ui->setupUi(this);

    QSqlQuery query;
    if(!query.exec("SELECT id, patient, date FROM prescription WHERE handled IS NOT TRUE")) {
        QMessageBox::critical(this, "数据库错误1", query.lastError().text());
        return;
    }

    ui->tableWidget_1->setColumnCount(3);
    ui->tableWidget_2->setColumnCount(4);

    QStringList head;
    head.append("流水号");
    head.append("病人");
    head.append("开单日期");
    ui->tableWidget_1->setHorizontalHeaderLabels(head);
    ui->tableWidget_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    head.clear();
    head.append("药名");
    head.append("条码");
    head.append("出库量");
    head.append("现有量");
    ui->tableWidget_2->setHorizontalHeaderLabels(head);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int cnt = 0;
    while(query.next()) {
        QString id = query.value(0).toString();
        QString patient = query.value(1).toString();
        QString date = query.value(2).toString();

        QTableWidgetItem* a = new QTableWidgetItem(id);
        QTableWidgetItem* b = new QTableWidgetItem(patient);
        QTableWidgetItem* c = new QTableWidgetItem(date);

        ui->tableWidget_1->insertRow(cnt);
        ui->tableWidget_1->setItem(cnt, 0, a);
        ui->tableWidget_1->setItem(cnt, 1, b);
        ui->tableWidget_1->setItem(cnt, 2, c);

        ++cnt;
    }
    ui->pushButton_1->setEnabled(false);
}

StockOutConfirmDialog::~StockOutConfirmDialog()
{
    delete ui;
}

void StockOutConfirmDialog::on_pushButton_1_clicked()
{
    if(ui->tableWidget_1->currentItem() == nullptr)
        return;
    // 这里应该将presciprtion表中的handled改成true,
    // 并且修改medicine表中的number,
    // 并且在m_xxx表中添加该药的出库记录
    // 并且删除两个表中项目
    QString p_id = ui->tableWidget_1->item(ui->tableWidget_1->currentRow(), 0)->text();
    ui->tableWidget_1->removeRow(ui->tableWidget_1->currentRow());
    QSqlQuery query;
    query.prepare("UPDATE prescription "
                  "SET handled = TRUE "
                  "WHERE id = :id");
    query.bindValue(":id", p_id);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误4", query.lastError().text());
        return;
    }

    QString medicine_table = QString("p_%1").arg(p_id);

    QString str("SELECT medicine_id, number FROM ");
    str.append(medicine_table);
    if(!query.exec(str)) {
        QMessageBox::critical(this, "数据库错误5", query.lastError().text());
        return;
    }

    while(query.next()) {
        int m_id = query.value(0).toInt();
        int num = query.value(1).toInt();

        QSqlQuery q;
        q.prepare("UPDATE medicine SET number = number - :num WHERE id = :id");
        q.bindValue(":num", num);
        q.bindValue(":id", m_id);
        if(!q.exec()) {
            QMessageBox::critical(this, "数据库错误6", query.lastError().text());
            break;
        }

        QString record_table = QString("m_%1").arg(m_id);
        str = QString("INSERT INTO %1 (date, number) "
                      "VALUES ('%2', %3)").arg(record_table,
                                             QDate::currentDate().toString(Qt::DateFormat::ISODate),
                                             QString("-%1").arg(num));
        if(!q.exec(str)) {
            QMessageBox::critical(this, "数据库错误7", query.lastError().text());
            break;
        }
    }

    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->pushButton_1->setEnabled(false);
}

void StockOutConfirmDialog::on_tableWidget_1_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if(current != nullptr && previous != nullptr && current->row() == previous->row())
        return;

    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->pushButton_1->setEnabled(false);

    if(current == nullptr)
        return;

    QString p_id = ui->tableWidget_1->item(current->row(), 0)->text();
    QString medicine_table = QString("p_%1").arg(p_id);

    QSqlQuery query;
    QString str("SELECT medicine_id, number FROM ");
    str.append(medicine_table);
    if(!query.exec(str)) {
        QMessageBox::critical(this, "数据库错误2", query.lastError().text());
        return;
    }

    bool flag = true;
    int cnt = 0;
    while(query.next()) {
        QSqlQuery q;
        q.prepare("SELECT code, name, number FROM medicine WHERE id = :id");
        q.bindValue(":id", query.value(0));
        if(!q.exec()) {
            QMessageBox::critical(this, "数据库错误3", query.lastError().text());
            break;
        }
        q.next();

        QTableWidgetItem* a = new QTableWidgetItem(q.value(1).toString());
        QTableWidgetItem* b = new QTableWidgetItem(q.value(0).toString());
        QTableWidgetItem* c = new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem* d = new QTableWidgetItem(q.value(2).toString());

        if(q.value(2).toInt() < query.value(1).toInt()) {
            c->setBackgroundColor(Qt::green);
            d->setBackgroundColor(Qt::green);
            flag = false;
        }

        ui->tableWidget_2->insertRow(cnt);
        ui->tableWidget_2->setItem(cnt, 0, a);
        ui->tableWidget_2->setItem(cnt, 1, b);
        ui->tableWidget_2->setItem(cnt, 2, c);
        ui->tableWidget_2->setItem(cnt, 3, d);
        ++cnt;
    }
    ui->pushButton_1->setEnabled(flag);
}

