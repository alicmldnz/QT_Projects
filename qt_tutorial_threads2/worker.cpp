#include "worker.h"
#include <QDebug>
Worker::Worker(QObject *parent)
    : QObject{parent}
{}
void Worker::doWork2() {
    QString result = "çalıştım";
    for (int i ; i<300000; i++) qDebug() << "Worker:" << i ;
    qDebug() << result;
    emit resultReady2(result);
}
void Worker::doWork3() {
    QString result = "yandan çalıştım";
    for (int a ; a < 300000; a++) qDebug() << "CoWorker" << a;
    qDebug() << result;
    emit resultReady3(result);
}
