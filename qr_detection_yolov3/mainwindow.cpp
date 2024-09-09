#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QR Detection");
    resize(800, 600);

    label = new QLabel(this);
    setCentralWidget(label);

    // Load class names and YOLOv3-tiny model
    classes = loadClassNames("path_to_qrcode.names");
    net = cv::dnn::readNetFromDarknet("path_to_qrcode-yolov3-tiny.cfg", "path_to_qrcode-yolov3-tiny.weights");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);

    // Start video capture thread
    videoThread = new VideoCaptureThread(this);
    connect(videoThread, &VideoCaptureThread::newFrame, this, &MainWindow::processFrame);
    videoThread->start();

    // Create a timer to process and display frames
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);
    timer->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
    videoThread->quit();
    videoThread->wait();
}
void MainWindow::processFrame(const cv::Mat& frame) {
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1 / 255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    net.forward(outs, getOutputsNames(net));

    processedFrame = frame.clone();
    postprocess(processedFrame, outs);
}
void MainWindow::updateDisplay() {
    if (!processedFrame.empty()) {
        // Convert BGR to RGB if needed
        cv::Mat rgbFrame;
        cv::cvtColor(processedFrame, rgbFrame, cv::COLOR_BGR2RGB);

        QImage img(rgbFrame.data, rgbFrame.cols, rgbFrame.rows, rgbFrame.step, QImage::Format_RGB888);
        label->setPixmap(QPixmap::fromImage(img).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
void MainWindow::postprocess(cv::Mat& frame, const std::vector<cv::Mat>& outs) {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    int frameHeight = frame.rows;
    int frameWidth = frame.cols;

    for (auto& out : outs) {
        float* data = (float*)out.data;
        for (int j = 0; j < out.rows; ++j, data += out.cols) {
            cv::Mat scores = out.row(j).colRange(5, out.cols);
            cv::Point classIdPoint;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > 0.6) {
                int centerX = (int)(data[0] * frameWidth);
                int centerY = (int)(data[1] * frameHeight);
                int width = (int)(data[2] * frameWidth);
                int height = (int)(data[3] * frameHeight);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, 0.6, 0.5, indices);

    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        cv::rectangle(frame, box, cv::Scalar(0, 0, 255), 2);

        QString label = QString("%1: %2").arg(classes[classIds[idx]]).arg(confidences[idx]);
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label.toStdString(), cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        top = std::max(box.y, labelSize.height);
        cv::rectangle(frame, cv::Point(box.x, top - labelSize.height), cv::Point(box.x + labelSize.width, top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
        cv::putText(frame, label.toStdString(), cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
    }
}

std::vector<cv::String> MainWindow::getOutputsNames(const cv::dnn::Net& net) {
    static std::vector<cv::String> names;
    if (names.empty()) {
        std::vector<int> outLayers = net.getUnconnectedOutLayers();
        std::vector<cv::String> layersNames = net.getLayerNames();
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

QStringList MainWindow::loadClassNames(const QString& path) {
    QStringList classNames;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            classNames << in.readLine().trimmed();
        }
        file.close();
    }
    return classNames;
}
