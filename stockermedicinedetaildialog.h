#ifndef STOCKERMEDICINEDETAILDIALOG_H
#define STOCKERMEDICINEDETAILDIALOG_H

#include <QDialog>

namespace Ui {
class StockerMedicineDetailDialog;
}

class StockerMedicineDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockerMedicineDetailDialog(const QString& m_id,
                                         QWidget *parent = nullptr);
    ~StockerMedicineDetailDialog();

    QString m_id;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::StockerMedicineDetailDialog *ui;
};

#endif // STOCKERMEDICINEDETAILDIALOG_H
