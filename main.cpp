#include "logindialog.h"
#include "doctorwindow.h"
#include "stockerwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QtSql>

QSqlDatabase db;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("rn7s2");
    app.setOrganizationDomain("rn7s2.cn");
    app.setApplicationName("Medical Information System");

    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.setIniCodec("UTF-8");
    if(!ini.contains("User/type")) {
        ini.setValue("User/type", 2);
        ini.setValue("Server/address", "");
        ini.setValue("Server/port", "");
        ini.setValue("Server/database", "");
        ini.setValue("Server/username", "");
        ini.setValue("Server/password", "");
    }
    int type = ini.value("User/type").toInt();

    LoginDialog dialog(type);
    if(dialog.exec() != QDialog::Accepted)
        return 0;
    ini.setValue("User/type", dialog.type);

    int port = ini.value("Server/port").toInt();
    QString server = ini.value("Server/address").toString();
    QString db_name = ini.value("Server/database").toString();
    QString username = ini.value("Server/username").toString();
    QString password = ini.value("Server/password").toString();

    db = QSqlDatabase::addDatabase("QMARIADB");
    db.setHostName(server);
    db.setPort(port);
    db.setDatabaseName(db_name);
    db.setUserName(username);
    db.setPassword(password);

    if(!db.open()) {
        QMessageBox::critical(nullptr, "数据库错误0", db.lastError().text());
        return 1;
    }

    DoctorWindow dw;
    StockerWindow sw;

    if(dialog.type == 0) {
        dw.setWindowFlags(Qt::Window);
        dw.setWindowState(Qt::WindowMaximized);
        dw.show();
    } else if(dialog.type == 1) {
        sw.setWindowFlags(Qt::Window);
        sw.setWindowState(Qt::WindowMaximized);
        sw.show();
    } else {
        dw.move(100, 100);
        sw.move(500, 200);
        dw.show();
        sw.show();
    }

    return app.exec();
}
