#ifndef STOCKRECORDVIEWDIALOG_H
#define STOCKRECORDVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class StockRecordViewDialog;
}

class StockRecordViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockRecordViewDialog(const QString& m_id,
                                   QWidget *parent = nullptr);
    ~StockRecordViewDialog();

private slots:
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::StockRecordViewDialog *ui;
};

#endif // STOCKRECORDVIEWDIALOG_H
