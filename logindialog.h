#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(const int& usertype, QWidget *parent = nullptr);
    ~LoginDialog();

    int type;

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
