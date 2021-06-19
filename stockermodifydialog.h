#ifndef STOCKERMODIFYDIALOG_H
#define STOCKERMODIFYDIALOG_H

#include <QDialog>

namespace Ui {
class StockerModifyDialog;
}

class StockerModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockerModifyDialog(const QString& m_id,
                                 QWidget *parent = nullptr);
    ~StockerModifyDialog();
    void accept() override;

    QString m_id;

private:
    Ui::StockerModifyDialog *ui;
};

#endif // STOCKERMODIFYDIALOG_H
