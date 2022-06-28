#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QMainWindow>
#include <QCoreApplication>
#include "user.h"
#include "maindatabase.h"

namespace Ui {
class LoginSystem;
}

class LoginSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginSystem(QWidget *parent = 0);
    ~LoginSystem();
    bool Login(QString u, QString p);
    bool loggedIn;
    QString picName;
    QString picDir = QCoreApplication::applicationDirPath()+"/../../LogSys/users/avatar";
    void delay(int);
//    QSqlTableModel* tblMdl;

private slots:
    void on_loginButton_clicked();

    void on_completeRegButton_clicked();

    void on_backButton_clicked();

    void on_regButton_clicked();

    void on_winStack_currentChanged(int arg1);

    void on_uplButton_clicked();

    void on_checkBox_showpass_stateChanged(int arg1);

    void on_showpassforsignup_stateChanged(int arg1);

    void on_forgetpassbtn_clicked();

    void on_backtologinforgetpass_clicked();

    void on_showpassforforgetpass_clicked();

private:
    Ui::LoginSystem *ui;
    user inneruser;
    maindatabase *database;
    QString username;
    QString password;
};

#endif // LOGINSYSTEM_H
