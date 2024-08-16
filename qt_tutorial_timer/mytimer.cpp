#include "mytimer.h"
#include <QtCore>
#include <QtDebug>

MyTimer::MyTimer()
{
    mTimer = new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),
               this,SLOT(MySlot()));

    mTimer->start(1000);
}

void MyTimer::MySlot()
{
    qDebug() << "timer is executed";
}
