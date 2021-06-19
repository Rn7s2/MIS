#ifndef STOCKOUTCONFIRMDIALOG_H
#define STOCKOUTCONFIRMDIALOG_H

#include <QDialog>

class QTableWidgetItem;

namespace Ui {
class StockOutConfirmDialog;
}

class StockOutConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockOutConfirmDialog(QWidget *parent = nullptr);
    ~StockOutConfirmDialog();

private slots:
    void on_pushButton_1_clicked();
    void on_tableWidget_1_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::StockOutConfirmDialog *ui;
};

#endif // STOCKOUTCONFIRMDIALOG_H
