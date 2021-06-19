#ifndef STOCKERADDNEWDIALOG_H
#define STOCKERADDNEWDIALOG_H

#include <QDialog>

namespace Ui {
class StockerAddNewDialog;
}

class StockerAddNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockerAddNewDialog(QWidget *parent = nullptr);
    ~StockerAddNewDialog();
    void accept() override;

    QString name, code, price, number, expiration, dosage;

private:
    Ui::StockerAddNewDialog *ui;
};

#endif // STOCKERADDNEWDIALOG_H
