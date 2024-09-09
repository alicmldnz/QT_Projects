#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // qDebug() << QThread::currentThreadId() << "main thread";
    // *flag = false;

    // Capturer Thread starts the camera and sends frame to Process Frame
    capturer = new Capturer;
    capturer->moveToThread(&capturerThread);
    connect(&capturerThread, &QThread::finished, capturer, &QObject::deleteLater);
    connect(this, &MainWindow::operate, capturer, &Capturer::start);
    this-> StartCapturer();

    // Convert Thread converts QFrame to cvMat for Detection Process
    convert = new Convert;
    convert->moveToThread(&convertThread);
    connect(&convertThread, &QThread::finished, convert, &QObject::deleteLater);
    connect(capturer, &Capturer::frameReady, convert, &Convert::processFrame);
    // ProcessFrame emits imGrayReady and imReady
     // Image with bounding box is sent to convert RGB
    this-> StartConvert();

    // Performs detection and Bounding Box drawing operations
    detection = new Detection;
    detection->moveToThread(&detectionThread);
    connect(&detectionThread, &QThread::finished, detection, &QObject::deleteLater);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    connect(convert, &Convert::imGrayReady, detection, &Detection::detectImg); // imGray is sent to detectImg to detect QRCode
    // detectImg emits imReady(imGray) with bounding box from drawBoundingBox
    qRegisterMetaType<cv::Mat>("cv::Mat");
    connect(detection, &Detection::imReady, convert, &Convert::convGraytoRgb); // Im is converted to RGB
    // // convGraytoRgb emits detectedImReady, changeFlag
    // connect(convert, &Convert::changeFlag, this, &MainWindow::signalControllerFlag);
    this-> StartDetection();

    // Streams Frame
    streamer = new Streamer;
    streamer->moveToThread(&streamerThread);
    connect(&streamerThread, &QThread::finished, streamer, &QObject::deleteLater);
    connect(this, &MainWindow::operate, streamer, &Streamer::initStream);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    connect(convert, &Convert::detectedImReady, streamer, &Streamer::updateFrame); // Im with QRCode is sent to updateFrame
    connect(convert, &Convert::imReady, streamer, &Streamer::updateFrame); // Im with no QRCode is sent to updateFrame
    this-> StartStreamer();
}

MainWindow::~MainWindow()
{
    delete ui;
    capturerThread.quit();
    capturerThread.wait();
    streamerThread.quit();
    streamerThread.wait();
    detectionThread.quit();
    detectionThread.wait();
    convertThread.quit();
    convertThread.wait();
}

// void MainWindow::signalControllerFlag(){
//     *flag = true;
//     qDebug() << " flag changed";
// }



void MainWindow::StartCapturer(){
    capturerThread.start();
    Q_EMIT operate();
}
void MainWindow::StartConvert(){
    convertThread.start();
}
void MainWindow::StartStreamer(){
    streamerThread.start();
    Q_EMIT operate();
}
void MainWindow::StartDetection(){
    detectionThread.start();
}
