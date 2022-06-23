#ifndef DIALOGFORCHANNEL_H
#define DIALOGFORCHANNEL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include "mainclass.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QPushButton;

class DialogForChannel: public QDialog
{
    Q_OBJECT
public:
    DialogForChannel(bool isAdmin , int IDC , QVector<int> memID ,QVector<QString> nameMem ,
QVector<QString> Admin, QWidget *parent = nullptr );

private:
    QTextEdit* Admins;
    QTextEdit* members;
    QPushButton* addAdmin;
    QListWidget* membersList;


};

#endif // DIALOGFORCHANNEL_H
