#ifndef DETECTION_H
#define DETECTION_H
#include <QObject>
#include <QVideoFrame>

class Detection: public QObject
{
    Q_OBJECT
public:
    Detection();
public Q_SLOTS:
    void processFrame(const QVideoFrame &frame);
};
#endif // DETECTION_H


