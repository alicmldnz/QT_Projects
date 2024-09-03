#include "detection.h"
#include <QThread>
#include <QDebug>
#include <zbar.h>
Detection::Detection(QObject *parent)
    : QObject{parent}
{}

void Detection::detectImg(cv::Mat &imGray)
{
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    int width = imGray.cols;
    int height = imGray.rows;
    uchar *raw = (uchar *)imGray.data;
    zbar::Image zbarImage(width, height, "Y800", raw, width * height);
    cv::imwrite("/opt/ali/imgray.png",imGray);
    int n = scanner.scan(zbarImage);
    QVector<cv::Point> points;
    if (n>0)
    {
        for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol)
        {
            std::string myData = symbol->get_data();
            qDebug() << "QR Code Detected:" << QString::fromStdString(myData);
            for (int i = 0; i < symbol->get_location_size(); ++i)
            {
                int x = symbol->get_location_x(i);
                int y = symbol->get_location_y(i);
                points.push_back(cv::Point(x, y));
            }
            drawBoundingBox(points, imGray);
        }
    }
    else
    {
    qDebug() << "No QR Code Detected";
    }
    // return points;
}

void Detection::drawBoundingBox(QVector<cv::Point> points, cv::Mat &imGray)
{
    std::vector<cv::Point> pointsarray(points.begin(), points.end());
    //Draw Bounding Box
    cv::polylines(imGray, pointsarray, true, cv::Scalar(0, 0, 0), 2);
    // return im;
    // cv::imwrite("/opt/ali/boundingim.png",imGray);
    Q_EMIT imReady(imGray);
}


// void Detection::processFrame(const QVideoFrame &frame)
// {
//     if (!frame.isValid()) {
//         qDebug() << "Frame is not valid";
//         return;
//     }
//     // qDebug() << QThread::currentThreadId() << " Detection::process Frame";
//     QVideoFrame cloneFrame(frame);
//     cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
//     cv::Mat imGray = convQFrametoMat(cloneFrame);
//     cv::Mat im;
//     cv::cvtColor(imGray, im, cv::COLOR_GRAY2RGB); // im = RGB
//     Q_EMIT imReady(im);
//     // QVector<cv::Point> points = detectImg(imGray);
//     // if (!points.isEmpty())
//     // {
//     //     im = drawBoundingBox(points, im);
//     //     Q_EMIT imReady(im);
//     // }
//     cloneFrame.unmap();
// }

// cv::Mat Detection::convQFrametoMat(QVideoFrame cloneFrame)
// {
//     cv::Mat im(cloneFrame.height(), cloneFrame.width(), CV_8UC1, (void*)cloneFrame.bits(), cloneFrame.bytesPerLine()); //Gray
//     return im;
// }


