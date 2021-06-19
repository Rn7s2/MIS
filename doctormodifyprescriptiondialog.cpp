#include "doctormodifyprescriptiondialog.h"
#include "quicksearchdialog.h"
#include "stockeraddexistingdialog.h"
#include "ui_doctormodifyprescriptiondialog.h"
#include <QtSql>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>

DoctorModifyPrescriptionDialog::DoctorModifyPrescriptionDialog(const QStringList& lst,
                                                               QWidget *parent) :
    QDialog(parent), ui(new Ui::DoctorModifyPrescriptionDialog)
{
    ui->setupUi(this);
    this->lst = lst;

    ui->tableWidget->setColumnCount(4);

    QStringList head;
    head.append("名称");
    head.append("数量");
    head.append("用法用量");
    head.append("价格");
    ui->tableWidget->setHorizontalHeaderLabels(head);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // set data;
    ui->lineEdit_1->setText(lst[2]);
    ui->lineEdit_2->setText(lst[5]);
    ui->spinBox->setValue(lst[3].toInt());
    if(lst[4] == "男")
        ui->comboBox->setCurrentIndex(0);
    else
        ui->comboBox->setCurrentIndex(1);

    // show current medicines.
    QString medicine_table = QString("p_%1").arg(lst[0]);
    QSqlQuery query;
    QString str("SELECT medicine_id, number FROM ");
    str.append(medicine_table);
    if(!query.exec(str)) {
        QMessageBox::critical(this, "数据库错误33", query.lastError().text());
        return;
    }

    int cnt = 0;
    while(query.next()) {
        QSqlQuery q;
        q.prepare("SELECT id, name, price, dosage FROM medicine WHERE id = :id");
        q.bindValue(":id", query.value(0));
        if(!q.exec()) {
            QMessageBox::critical(this, "数据库错误34", query.lastError().text());
            break;
        }
        q.next();
        m_ids.append(q.value(0).toInt());
        QString name = q.value(1).toString();
        QString dosage = q.value(3).toString();
        int num = query.value(1).toInt();
        double price = q.value(2).toDouble();

        ui->tableWidget->insertRow(cnt);
        ui->tableWidget->setItem(cnt, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(cnt, 1, new QTableWidgetItem(QString::number(num)));
        ui->tableWidget->setItem(cnt, 2, new QTableWidgetItem(dosage));
        ui->tableWidget->setItem(cnt, 3, new QTableWidgetItem(QString::number(price)));
        ++cnt;
    }
    makeDocument();
}

void DoctorModifyPrescriptionDialog::makeDocument()
{
    this->repaint(QRect(ui->widget->x(),
                        ui->widget->y(),
                        ui->widget->width(),
                        ui->widget->height()));
}

QPixmap DoctorModifyPrescriptionDialog::makePixmap()
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

    int y = 850;
    double total_price = 0;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        QString name = ui->tableWidget->item(i, 0)->text();
        int num = ui->tableWidget->item(i, 1)->text().toInt();
        QString dosage = ui->tableWidget->item(i, 2)->text();
        double price = ui->tableWidget->item(i, 3)->text().toDouble();
        total_price += (double)num * price;

        painter.drawText(QRect(350, y, 1000, 80), name + " x" + QString::number(num));
        y += 60;
        painter.drawText(QRect(350, y, 1000, 80), "    " + dosage);
        y += 80;
    }

    painter.drawText(QRect(460, 1890, 230, 80), QString::number(total_price) + " 元");

    return pix;
}

DoctorModifyPrescriptionDialog::~DoctorModifyPrescriptionDialog()
{
    delete ui;
}

void DoctorModifyPrescriptionDialog::paintEvent(QPaintEvent *event)
{
    QPixmap pix(makePixmap());

    QRect rect(ui->widget->x(),
               ui->widget->y(),
               ui->widget->width(),
               ui->widget->height());
    QPainter p(this);
    p.drawPixmap(rect, pix, pix.rect());

    QDialog::paintEvent(event);
}

void DoctorModifyPrescriptionDialog::on_pushButton_1_clicked()
{
    QuickSearchDialog dialog(this);
    dialog.setWindowFlags(Qt::Window);
    dialog.setWindowState(Qt::WindowMaximized);
    if(dialog.exec() != QDialog::Accepted)
        return;

    QString m_id = dialog.m_id;
    QSqlQuery query;
    query.prepare("SELECT name, price, dosage FROM medicine WHERE id = :id");
    query.bindValue(":id", m_id);
    if(!query.exec()) {
        QMessageBox::critical(this, "数据库错误20", query.lastError().text());
        return;
    }

    StockerAddExistingDialog d(this);
    if(d.exec() != QDialog::Accepted)
        return;

    while(query.next()) {
        QString name = query.value(0).toString();
        QString num = QString::number(d.num);
        QString price = query.value(1).toString();
        QString dosage = query.value(2).toString();

        int cur = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(cur);

        ui->tableWidget->setItem(cur, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(cur, 1, new QTableWidgetItem(num));
        ui->tableWidget->setItem(cur, 2, new QTableWidgetItem(dosage));
        ui->tableWidget->setItem(cur, 3, new QTableWidgetItem(price));
    }
    m_ids.push_back(m_id.toInt());
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_pushButton_2_clicked()
{
    if(ui->tableWidget->currentItem() == nullptr)
        return;
    m_ids.removeAt(ui->tableWidget->currentRow());
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_lineEdit_1_textChanged(const QString &arg1)
{
    lst[2] = arg1;
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_spinBox_textChanged(const QString &arg1)
{
    lst[3] = arg1;
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    lst[4] = arg1;
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    lst[5] = arg1;
    makeDocument();
}

void DoctorModifyPrescriptionDialog::on_pushButton_3_clicked()
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.setIniCodec("UTF-8");
    QSqlQuery query;
    QString sql = QString("UPDATE prescription SET "
                          "patient = '%1', age = %2, sex = %3, diagnosis = '%4' "
                          "WHERE id = %5").arg(ui->lineEdit_1->text(),
                                               ui->spinBox->text(),
                                               QString::number(ui->comboBox->currentIndex()),
                                               ui->lineEdit_2->text(),
                                               lst[0]);

    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误33", query.lastError().text());
        return;
    }

    QString m_table = "p_" + lst[0];

    sql = QString("DELETE FROM ");
    sql += m_table;
    if(!query.exec(sql)) {
        QMessageBox::critical(this, "数据库错误34", query.lastError().text());
        return;
    }

    const auto& w = ui->tableWidget;
    for(int i = 0; i < w->rowCount(); i++) {
        sql = QString("INSERT INTO %1 (medicine_id, number) "
                      "VALUES (%2, %3)").arg(m_table,
                                             QString::number(m_ids[i]),
                                             w->item(i, 1)->text());
        if(!query.exec(sql)) {
            QMessageBox::critical(this, "数据库错误25", query.lastError().text());
            break;
        }
    }

    if(QMessageBox::question(this, "打印", "是否打印处方？") == QMessageBox::Yes) {
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

    accept();
}
