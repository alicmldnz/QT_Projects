#include "mythread.h"
#include <QDebug>
#include <QThread>
#include <QMutex>
MyThread::MyThread(QThread *parent)
    : QThread{parent}
{}

void MyThread::run()
{
    for (int i = 0; i<100; i++){
        QMutex mutex;
        mutex.lock();
        if(this->Stop){
            break;
        }
        mutex.unlock();

        emit NumberChanged(i);

    }
}

