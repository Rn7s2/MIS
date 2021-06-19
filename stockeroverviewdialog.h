#ifndef STOCKEROVERVIEWDIALOG_H
#define STOCKEROVERVIEWDIALOG_H

#include <QDialog>

class QTableWidgetItem;

namespace Ui {
class StockerOverViewDialog;
}

class StockerOverViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockerOverViewDialog(QWidget *parent = nullptr);
    ~StockerOverViewDialog();

private slots:
    void on_tableWidget_1_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::StockerOverViewDialog *ui;
};

#endif // STOCKEROVERVIEWDIALOG_H
