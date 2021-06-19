#ifndef STOCKERWINDOW_H
#define STOCKERWINDOW_H

#include <QMainWindow>

namespace Ui {
class StockerWindow;
}

class StockerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StockerWindow(QWidget *parent = nullptr);
    ~StockerWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::StockerWindow *ui;
};

#endif // STOCKERWINDOW_H
