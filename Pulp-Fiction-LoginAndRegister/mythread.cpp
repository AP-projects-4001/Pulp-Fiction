#include "mythread.h"

MyThread::MyThread(QWidget* parent)
    :QThread(parent)
{

}
void MyThread::run()
{
    for(;;)
    {
        sleep(10);
        emit NumberChange();
    }
}
