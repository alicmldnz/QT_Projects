#include "mythread.h"
#include <QThread>
#include "mainwindow.h"
MyThread::MyThread() {

}

void MyThread::doWork() {
    QString result = "worked";
    for (int i=0; i<300000; i++){
        qDebug() << i;

    }
    qDebug() << result;
    emit resultReady(result);
}
void MyThread::run() {
    doWork();
}

