#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include "mainclass.h"
#include "dialogforchannel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QPushButton;

class channelDialog :public QDialog, public mainClass
{
    Q_OBJECT
public:
    channelDialog(int ID , QString nameChannel , int IDC , QVector<int> memId,QVector<QString> nameMem ,
QVector<int> ADID,QVector<QString> Admins, QVector<QString> messageChannel ,QWidget *parent = nullptr );

public slots:
    void send_clicked();
    void info_clicked();

private:
    QVector<QString> nameOfmembers;
    QVector<QString> nemaOfAdmins;
    QVector<int> memberID;

    DialogForChannel* ob;
    int IDchannel;
    bool isAdmin = false;
};

#endif // CHANNELDIALOG_H
