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
    bool Stop = false;
signals:
    void NumberChange();
private:
    QMutex mutex;
};


#endif // MYTHREAD_H
