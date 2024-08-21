#ifndef CAPTURER_H
#define CAPTURER_H
#include <QObject>
#include <QVideoProbe>
#include <QCamera>
class Capturer : public QObject
{
    Q_OBJECT
public:
    Capturer();
public Q_SLOTS:
    void capture();
    void stopCam();
private:
    QVideoProbe *probe;
    QCamera *camera;
};

#endif // CAPTURER_H
