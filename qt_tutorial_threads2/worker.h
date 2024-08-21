#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
public slots:
    void doWork2();
    void doWork3();
signals:
    void resultReady2(const QString &r);
    void resultReady3(const QString &r);
};

#endif // WORKER_H
