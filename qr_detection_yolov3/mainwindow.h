#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <videocapturethread.h>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void processFrame(const cv::Mat& frame);
    void updateDisplay();

private:
    QLabel* label;
    cv::dnn::Net net;
    QStringList classes;
    std::vector<cv::Mat> outs;
    cv::Mat processedFrame;
    VideoCaptureThread* videoThread;
    std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);
    QStringList loadClassNames(const QString& path);
    void postprocess(cv::Mat& frame, const std::vector<cv::Mat>& outs);



};
#endif // MAINWINDOW_H
