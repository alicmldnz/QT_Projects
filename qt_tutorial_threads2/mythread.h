#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run() override;
    void doWork();

signals:
    void resultReady(const QString &s);
};

#endif // MYTHREAD_H
