#ifndef STOCKERADDEXISTINGDIALOG_H
#define STOCKERADDEXISTINGDIALOG_H

#include <QDialog>

namespace Ui {
class StockerAddExistingDialog;
}

class StockerAddExistingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockerAddExistingDialog(QWidget *parent = nullptr);
    ~StockerAddExistingDialog();
    void accept() override;

    int num;

private:
    Ui::StockerAddExistingDialog *ui;
};

#endif // STOCKERADDEXISTINGDIALOG_H
