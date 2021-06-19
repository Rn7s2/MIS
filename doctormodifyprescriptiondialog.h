#ifndef DOCTORMODIFYPRESCRIPTIONDIALOG_H
#define DOCTORMODIFYPRESCRIPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DoctorModifyPrescriptionDialog;
}

class DoctorModifyPrescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorModifyPrescriptionDialog(const QStringList& lst,
                                            QWidget *parent = nullptr);
    ~DoctorModifyPrescriptionDialog();

    QString p_id;

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_1_textChanged(const QString &arg1);
    void on_spinBox_textChanged(const QString &arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_pushButton_3_clicked();

private:
    void makeDocument();
    QPixmap makePixmap();

    QList<int> m_ids;
    QStringList lst;
    Ui::DoctorModifyPrescriptionDialog *ui;
};

#endif // DOCTORMODIFYPRESCRIPTIONDIALOG_H
