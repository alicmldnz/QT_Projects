#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QVBoxLayout>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <zbar.h>



QT_BEGIN_NAMESPACE
using namespace cv;
using namespace zbar;


namespace Ui {
class CameraWidget;
}
QT_END_NAMESPACE

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();
private slots:
    void processFrame();
private:
    Ui::CameraWidget *ui;
    /*QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    QTimer *timer;
    std::vector<std::string> myDataList;
    VideoSurface *videoSurface;*/
    VideoCapture cap;
    QLabel *imageLabel;
};
#endif // CAMERAWIDGET_H
