#ifndef QUICKSEARCHDIALOG_H
#define QUICKSEARCHDIALOG_H

#include <QDialog>

class QTableWidgetItem;

namespace Ui {
class QuickSearchDialog;
}

class QuickSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuickSearchDialog(QWidget *parent = nullptr);
    ~QuickSearchDialog();

    QString m_id;
    int num;

private slots:
    void on_pushButton_1_clicked();
    void on_lineEdit_1_textChanged(const QString &str);
    void on_tableWidget_1_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::QuickSearchDialog *ui;
};

#endif // QUICKSEARCHDIALOG_H
