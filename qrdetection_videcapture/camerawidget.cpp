#include "camerawidget.h"
#include "ui_camerawidget.h"
#include <QCamera>
#include <QtMultimedia>
#include <QVBoxLayout>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <QImage>
#include <QPixmap>
#include <QCamera>
#include <QDebug>
#include "videosurface.h"

/*CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
    camera = new QCamera(QCamera::availableDevices().at(1), this);
    viewfinder = new QCameraViewfinder(this);
    viewfinder->show();
    camera->setViewfinder(viewfinder);
    imageCapture = new QCameraImageCapture(camera, this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(viewfinder);
    setLayout(layout);

    connect(imageCapture, &QCameraImageCapture::imageCaptured, this, &CameraWidget::processCapturedImage);

    camera->start();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CameraWidget::captureImage);
    timer->start(500);  // 500ms aralıklarla görüntü yakala
}
CameraWidget::~CameraWidget()
{
    camera-> stop();
}
void CameraWidget::captureImage() {
    if (camera->state() == QCamera::ActiveState) {
        imageCapture->capture();
        qDebug() << "image captured";
    }
}

void CameraWidget::processCapturedImage(int id, const QImage &image) {
    Q_UNUSED(id);

    cv::Mat im(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
    qDebug() << id;
    cv::Mat imGray;
    cv::cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

    // Create zbar scanner
    zbar::ImageScanner scanner;

    // Configure scanner
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    int width = imGray.cols;
    int height = imGray.rows;
    uchar *raw = (uchar *)imGray.data;

    // Wrap image data in a zbar image
    zbar::Image zbarImage(width, height, "Y800", raw, width * height);
    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(zbarImage);

    if (n > 0) {
        for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
            std::string myData = symbol->get_data();
            qDebug() << "QR Code Detected:" << QString::fromStdString(myData);
        }
    } else {
        qDebug() << "No QR Code Detected";
    }
}*/

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent) , cap(0)
    , ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
}
