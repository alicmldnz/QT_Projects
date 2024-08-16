#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QObject>
#include <QString>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = nullptr);
    void run();
    void stop();
    QString name;
    bool Stop;
signals:
    void NumberChanged(int);
public slots:

};

#endif // MYTHREAD_H
