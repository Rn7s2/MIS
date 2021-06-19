#include "quicksearchdialog.h"
#include "ui_quicksearchdialog.h"
#include <QtSql>
#include <QMessageBox>

QuickSearchDialog::QuickSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuickSearchDialog)
{
    ui->setupUi(this);

    m_id = QString();

    ui->tableWidget_1->setColumnCount(5);

    QStringList head;
    head.append("序号");
    head.append("名称");
    head.append("条码");
    head.append("数量");
    head.append("用法用量");
    ui->tableWidget_1->setHorizontalHeaderLabels(head);
    ui->tableWidget_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QuickSearchDialog::~QuickSearchDialog()
{
    delete ui;
}

void QuickSearchDialog::on_pushButton_1_clicked()
{
    this->reject();
}

void QuickSearchDialog::on_lineEdit_1_textChanged(const QString &str)
{
    ui->tableWidget_1->clearContents();
    ui->tableWidget_1->setRowCount(0);
    if(str == QString())
        return;

    QSqlQuery query;
    QString sql = QString("SELECT id, code, name, number, dosage FROM medicine "
            "WHERE code LIKE '%%%1%%' OR name LIKE '%%%1%%'").arg(str);
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误8", query.lastError().text());
    }
    int cnt = 0;
    while(query.next()) {
        QString id = query.value(0).toString();
        QString code = query.value(1).toString();
        QString name = query.value(2).toString();
        QString number = query.value(3).toString();
        QString dosage = query.value(4).toString();

        QTableWidgetItem* a = new QTableWidgetItem(id);
        QTableWidgetItem* b = new QTableWidgetItem(name);
        QTableWidgetItem* c = new QTableWidgetItem(code);
        QTableWidgetItem* d = new QTableWidgetItem(number);
        QTableWidgetItem* e = new QTableWidgetItem(dosage);

        ui->tableWidget_1->insertRow(cnt);
        ui->tableWidget_1->setItem(cnt, 0, a);
        ui->tableWidget_1->setItem(cnt, 1, b);
        ui->tableWidget_1->setItem(cnt, 2, c);
        ui->tableWidget_1->setItem(cnt, 3, d);

        if(number.toInt() <= 2)
            d->setBackgroundColor(Qt::GlobalColor::blue);

        ui->tableWidget_1->setItem(cnt, 4, e);

        cnt++;
    }
}


void QuickSearchDialog::on_tableWidget_1_itemDoubleClicked(QTableWidgetItem *item)
{
    m_id = ui->tableWidget_1->item(item->row(), 0)->text();
    this->accept();
}
