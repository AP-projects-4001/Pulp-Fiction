#ifndef PVDIALOG_H
#define PVDIALOG_H

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

class pvDialog: public QDialog, public mainClass
{
    Q_OBJECT
public:
    pvDialog(int UID ,int FID ,QString name, QVector<QString> messageChannel ,QWidget *parent = nullptr );
public slots:
    void send_clicked();
private:
    int myID;
    int yourID;
};

#endif // PVDIALOG_H
