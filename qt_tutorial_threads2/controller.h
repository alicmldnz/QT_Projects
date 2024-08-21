#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Controller(QObject *parent = nullptr);
    Controller();
    ~Controller();
signals:
    void operate(const QString &);
};

#endif // CONTROLLER_H
