#ifndef GROUPDIALOG_H
#define GROUPDIALOG_H

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
class groupDialog : public QDialog , public mainClass
{
    Q_OBJECT
public:
    groupDialog(int ID , QString groupName , int IDC , QVector<int> memId,QVector<QString> nameMem ,
  QVector<int> ADID,QVector<QString> Admins, QVector<QString> groupMessage ,QWidget *parent = nullptr);

public slots:
    void send_clicked();
    void info_clicked();
private:
    QVector<QString> nameOfmembers;
    QVector<QString> nemaOfAdmins;
    QVector<int> memberID;

    DialogForChannel* ob;
    int IDgroup;
    bool isAdmin = false;

};

#endif // GROUPDIALOG_H
