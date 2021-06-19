#include "stockerwindow.h"
#include "ui_stockerwindow.h"
#include "quicksearchdialog.h"
#include "stockermodifydialog.h"
#include "stockeraddnewdialog.h"
#include "stockoutconfirmdialog.h"
#include "stockeroverviewdialog.h"
#include "stockeraddexistingdialog.h"
#include "stockermedicinedetaildialog.h"
#include <QtSql>
#include <QMessageBox>

StockerWindow::StockerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StockerWindow)
{
    ui->setupUi(this);
}

StockerWindow::~StockerWindow()
{
    delete ui;
}

// 查看总库
void StockerWindow::on_pushButton_1_clicked()
{
    StockerOverViewDialog d(this);
    d.setWindowFlags(Qt::Window);
    d.setWindowState(Qt::WindowMaximized);
    d.exec();
}

// 查看详情
void StockerWindow::on_pushButton_2_clicked()
{
    QuickSearchDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    if(dialog.exec() != QDialog::Accepted)
        return;
    StockerMedicineDetailDialog detail(dialog.m_id, this);
    detail.exec();
}

// 旧药入库
void StockerWindow::on_pushButton_3_clicked()
{
    // 修改medicine表中的number
    // 并且在m_xx表中增加入库项
    QuickSearchDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    if(dialog.exec() != QDialog::Accepted)
        return;
    StockerAddExistingDialog add(this);
    if(add.exec() != QDialog::Accepted)
        return;
    int num = add.num;

    QSqlQuery query;
    QString sql = QString("UPDATE medicine "
                          "SET number = number + %1 "
                          "WHERE id = %2").arg(QString::number(num), dialog.m_id);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误10", query.lastError().text());
        return;
    }

    QString record_table = QString("m_%1").arg(dialog.m_id);
    sql = QString("INSERT INTO %1 (date, number) "
                  "VALUES ('%2', %3)").arg(record_table,
                                         QDate::currentDate().toString(Qt::DateFormat::ISODate),
                                         QString::number(num));
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误11", query.lastError().text());
        return;
    }
}

// 新药入库
void StockerWindow::on_pushButton_4_clicked()
{
    StockerAddNewDialog d(this);
    if(d.exec() != QDialog::Accepted)
        return;

    QSqlQuery query;
    query.prepare("SELECT id FROM medicine "
                  "WHERE code = :code AND name = :name");
    query.bindValue(":code", d.code);
    query.bindValue(":name", d.name);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误16", query.lastError().text());
        return;
    }
    if(query.next()) {
        QMessageBox::critical(this, "重复的项目", "已经存在此项，请使用添加旧药功能");
        return;
    }

    QString sql = QString("INSERT INTO medicine "
                          "(code, name, price, number, expiration, dosage) "
                          "VALUES ('%1', '%2', %3, %4, '%5', '%6')")
            .arg(d.code, d.name, d.price, d.number, d.expiration, d.dosage);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误12", query.lastError().text());
        return;
    }

    query.prepare("SELECT id FROM medicine "
                  "WHERE code = :code AND name = :name");
    query.bindValue(":code", d.code);
    query.bindValue(":name", d.name);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误13", query.lastError().text());
        return;
    }
    query.next();
    QString id = query.value(0).toString();

    QString record_table = QString("m_%1").arg(id);
    sql = QString("CREATE TABLE `%1` ("
                  "`id` INT(11) NOT NULL AUTO_INCREMENT, "
                  "`date` TEXT NOT NULL COLLATE 'utf8_general_ci', "
                  "`number` INT(11) NOT NULL, "
                  "PRIMARY KEY (`id`) USING BTREE)"
                  "COLLATE='utf8_general_ci'"
                  "ENGINE=InnoDB").arg(record_table);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误14", query.lastError().text());
        return;
    }
    sql = QString("INSERT INTO %1 (date, number) "
                  "VALUES ('%2', %3)").arg(record_table,
                                           QDate::currentDate().toString(Qt::DateFormat::ISODate),
                                           d.number);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误15", query.lastError().text());
        return;
    }
}

// 确认出库
void StockerWindow::on_pushButton_5_clicked()
{
    StockOutConfirmDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    dialog.exec();
}

// 修改信息
void StockerWindow::on_pushButton_6_clicked()
{
    QuickSearchDialog dialog(this);
    if(dialog.exec() != QDialog::Accepted)
        return;
    StockerModifyDialog modify(dialog.m_id, this);
    modify.exec();
}

// 统计表单
void StockerWindow::on_pushButton_7_clicked()
{
    // 增加导出到Excel.csv功能
    QMessageBox::information(this, "功能未实现", "功能未实现");
}
