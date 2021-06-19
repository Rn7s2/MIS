#ifndef DOCTORNEWPRESCRIPTIONDIALOG_H
#define DOCTORNEWPRESCRIPTIONDIALOG_H

#include <QList>
#include <QDialog>

namespace Ui {
class DoctorNewPrescriptionDialog;
}

class DoctorNewPrescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorNewPrescriptionDialog(QWidget *parent = nullptr);
    ~DoctorNewPrescriptionDialog();

private slots:
    void on_lineEdit_1_textChanged(const QString &arg1);
    void on_spinBox_textChanged(const QString &arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::DoctorNewPrescriptionDialog *ui;
    QPixmap makePixmap();
    void makeDocument();

    QStringList lst;
    QList<int> m_ids;
};

#endif // DOCTORNEWPRESCRIPTIONDIALOG_H
