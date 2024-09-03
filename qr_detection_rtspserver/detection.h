#ifndef DETECTION_H
#define DETECTION_H
#include <QMutex>
#include <QObject>
#include <QVideoFrame>
#include <opencv2/opencv.hpp>

class Detection : public QObject
{
    Q_OBJECT
public:
    explicit Detection(QObject *parent = nullptr);
private:
    void drawBoundingBox(QVector<cv::Point> points, cv::Mat &im);
    QMutex mutex;
public Q_SLOTS:
    void detectImg(cv::Mat &imGray);
Q_SIGNALS:
    void imReady(cv::Mat im);
};

#endif // DETECTION_H
