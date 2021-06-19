#include "stockrecordviewdialog.h"
#include "ui_stockrecordviewdialog.h"

#include <QtSql>
#include <QMessageBox>

StockRecordViewDialog::StockRecordViewDialog(const QString& m_id,
                                             QWidget *parent) :
    QDialog(parent), ui(new Ui::StockRecordViewDialog)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QString table = "m_" + m_id;

    QSqlQuery query;
    if(!query.exec(QString("SELECT date, number FROM %1").arg(table))) {
        QMessageBox::critical(this, "数据库错误26", query.lastError().text());
        return;
    }

    int cnt = 0;
    while(query.next()) {
        QString date = query.value(0).toString();
        QString number = query.value(1).toString();

        ui->tableWidget->insertRow(cnt);
        ui->tableWidget->setItem(cnt, 0, new QTableWidgetItem(date));
        ui->tableWidget->setItem(cnt, 1, new QTableWidgetItem(number));

        ++cnt;
    }
}

StockRecordViewDialog::~StockRecordViewDialog()
{
    delete ui;
}

void StockRecordViewDialog::on_tableWidget_itemSelectionChanged()
{
    int in = 0, out = 0;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        bool flag = false;
        flag = flag | ui->tableWidget->isItemSelected(ui->tableWidget->item(i, 0));
        flag = flag | ui->tableWidget->isItemSelected(ui->tableWidget->item(i, 1));
        if(!flag)
            continue;
        int num = ui->tableWidget->item(i, 1)->text().toInt();
        if(num >= 0)
            in += num;
        else
            out += num;
    }
    out = -out;
    ui->lineEdit_1->setText(QString::number(out));
    ui->lineEdit_2->setText(QString::number(in));
}
