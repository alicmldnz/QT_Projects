#include "videocapturethread.h"

#include <QDebug>

VideoCaptureThread::VideoCaptureThread(QObject* parent)
    : QThread(parent), process(true) {
    if (!cap.open(0)) {  // Open the default camera
        qDebug() << "Error: Unable to open the camera";
        process = false;
    }
}

VideoCaptureThread::~VideoCaptureThread() {
    process = false;
    wait();  // Wait for the thread to finish
}
