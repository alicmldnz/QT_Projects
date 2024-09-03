#ifndef CONVERT_H
#define CONVERT_H
#include <QMutex>
#include <QObject>
#include <QVideoFrame>
#include <opencv2/opencv.hpp>
class Convert : public QObject
{
    Q_OBJECT
public:
    explicit Convert(QObject *parent = nullptr);
private:
    cv::Mat convQFrametoMat(QVideoFrame);
    QMutex mutex;

public Q_SLOTS:
    void processFrame(const QVideoFrame &frame);
    void convGraytoRgb(cv::Mat imGray);
Q_SIGNALS:
    void imReady(cv::Mat &im);
    void imGrayReady(cv::Mat &imGray);
    void detectedImReady(cv::Mat &im);
    void changeFlag();
};

#endif // CONVERT_H
