#include "mythread.h"

MyThread::MyThread(QWidget* parent)
    :QThread(parent)
{

}
void MyThread::run()
{
    for(;;)
    {
        mutex.lock();
        if(this->Stop) break;
        mutex.unlock();
        sleep(10);
        emit NumberChange();

    }
}
