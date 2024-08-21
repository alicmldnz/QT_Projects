#include "detection.h"
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <QDebug>
Detection::Detection() {}


void Detection::processFrame(const QVideoFrame &frame)
{
    if (!frame.isValid()) {
        qDebug() << "Frame is not valid";
        return;
    }

    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

    // Convert QVideoFrame to cv::Mat
    cv::Mat im(cloneFrame.height(), cloneFrame.width(), CV_8UC4, (void*)cloneFrame.bits(), cloneFrame.bytesPerLine());
    cv::Mat imGray;
    cv::cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

    // Create zbar scanner
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    int width = imGray.cols;
    int height = imGray.rows;
    uchar *raw = (uchar *)imGray.data;

    // Wrap image data in a zbar image
    zbar::Image zbarImage(width, height, "Y800", raw, width * height);
    int n = scanner.scan(zbarImage);

    if (n > 0) {
        for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
            std::string myData = symbol->get_data();
            qDebug() << "QR Code Detected:" << QString::fromStdString(myData);

            // Draw a rectangle around the detected QR code
            cv::Rect rect(symbol->get_location_x(0), symbol->get_location_y(0),
                          symbol->get_location_x(2) - symbol->get_location_x(0),
                          symbol->get_location_y(2) - symbol->get_location_y(0));
            cv::rectangle(im, rect, cv::Scalar(0, 255, 0), 3);

            // Update the Streamer with the current frame
            streamer->updateFrame(im);
            qDebug() << "im was sent to streamer from mainwindow";
        }
    } else {
        qDebug() << "No QR Code Detected";
    }

    cloneFrame.unmap();
}
