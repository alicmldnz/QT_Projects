#ifndef VIDEOCAPTURETHREAD_H
#define VIDEOCAPTURETHREAD_H
#include <opencv2/opencv.hpp>
#include <QThread>
class VideoCaptureThread : public QThread {
    Q_OBJECT
    void run() override {
        while (process) {
            cv::Mat frame;
            if (!cap.read(frame)) break;

            emit newFrame(frame);
        }
    }


public:
    explicit VideoCaptureThread(QObject* parent = nullptr);
    ~VideoCaptureThread();

signals:
    void newFrame(const cv::Mat& frame);

private:
    cv::VideoCapture cap;
    std::atomic<bool> process;
};

#endif // VIDEOCAPTURETHREAD_H
