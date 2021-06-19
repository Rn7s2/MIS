#ifndef DOCTORVIEWPRESCRIPTIONDIALOG_H
#define DOCTORVIEWPRESCRIPTIONDIALOG_H

#include <QDialog>

class QTableWidgetItem;

namespace Ui {
class DoctorViewPrescriptionDialog;
}

class DoctorViewPrescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorViewPrescriptionDialog(QWidget *parent = nullptr);
    ~DoctorViewPrescriptionDialog();

private slots:
    void on_lineEdit_textChanged(const QString &str);
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void makeDocument();
    QPixmap makePixmap();
    void enableButtons();
    void disableButtons();
    void FuzzySearchPrescription(const QString& str);

    Ui::DoctorViewPrescriptionDialog *ui;
    QStringList lst;
};

#endif // DOCTORVIEWPRESCRIPTIONDIALOG_H
