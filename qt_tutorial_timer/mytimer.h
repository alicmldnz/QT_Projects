#ifndef MYTIMER_H
#define MYTIMER_H
#include <QTimer>
#include <QtCore>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    MyTimer();
    QTimer *mTimer;
public slots:
    void MySlot();
};

#endif // MYTIMER_H
