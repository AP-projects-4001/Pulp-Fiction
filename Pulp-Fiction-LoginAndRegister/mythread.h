#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QtCore>
class MyThread :public QThread
{
    Q_OBJECT
public:
    MyThread(QWidget* parent = 0);
    void run();
signals:
    void NumberChange();
private:

};


#endif // MYTHREAD_H
