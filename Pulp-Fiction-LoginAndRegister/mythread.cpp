#include "mythread.h"

MyThread::MyThread(QWidget* parent)
    :QThread(parent)
{

}
void MyThread::run()
{
    for(;;)
    {
        sleep(5);
        emit NumberChange();
    }
}
