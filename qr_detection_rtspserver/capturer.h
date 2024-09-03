#ifndef CAPTURER_H
#define CAPTURER_H
#include <QVideoProbe>
#include <QCamera>
#include <opencv2/opencv.hpp>
class Capturer : public QObject
{
    Q_OBJECT

public:
    explicit Capturer(QObject *parent = nullptr);
    ~Capturer();
     QVideoProbe *probe;
public Q_SLOTS:
    void start();
Q_SIGNALS:
    void frameReady(const QVideoFrame &frame);
private:
    QCamera *camera;



};

#endif // CAPTURER_H
