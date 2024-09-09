#include "convert.h"
#include <QDebug>
#include <QThread>
Convert::Convert(QObject *parent)
    : QObject{parent}
{}
void Convert::processFrame(const QVideoFrame &frame)
{
    mutex.lock();
    if (!frame.isValid()) {
        qDebug() << "Frame is not valid";
        return;
    }
    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
    cv::Mat im = convQFrametoMat(cloneFrame); // im = Gray
    cv::Mat imGray = im.clone();
    Q_EMIT imGrayReady(imGray); // for detection Gray is necessary
    cv::cvtColor(im, im, cv::COLOR_GRAY2RGB); // im = RGB
    // cv::cvtColor(imGray, im, cv::COLOR_GRAY2RGB); // im = RGB
    Q_EMIT imReady(im);
    // qDebug() << QThread::currentThreadId() << " Convert::process Frame";
    cloneFrame.unmap();
    mutex.unlock();
}
cv::Mat Convert::convQFrametoMat(QVideoFrame cloneFrame)
{
    // Conver QFrame to cvMat
    cv::Mat im(cloneFrame.height(), cloneFrame.width(), CV_8UC1, (void*)cloneFrame.bits(), cloneFrame.bytesPerLine()); //Gray
    return im;
}
void Convert::convGraytoRgb(cv::Mat imGray)
{
    mutex.lock();
    cv::Mat im;
    cv::cvtColor(imGray, im, cv::COLOR_GRAY2RGB); // im = RGB
    Q_EMIT detectedImReady(im);
    Q_EMIT changeFlag();
    mutex.unlock();
}
