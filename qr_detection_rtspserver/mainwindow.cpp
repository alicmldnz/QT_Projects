#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include "streamer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    streamer = new Streamer;
    streamer->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, streamer, &QObject::deleteLater);
    connect(this, &MainWindow::startOperation, streamer, &Streamer::capture);
    connect(streamer, &Streamer::resultReady2, this, &MainWindow::handelResult2);

    detection = new Detection;
    detection->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, detection, &QObject::deleteLater);
    connect(this, &MainWindow::startOperation, detection, &Detection::processFrame);
    connect(detection, &Detection::resultReady2, this, &MainWindow::handelResult2);

    capturer = new Capturer;
    capturer->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, capturer, &QObject::deleteLater);
    connect(this, &MainWindow::startOperation, capturer, &Capturer::Streamer);
    connect(capturer, &Capturer::resultReady2, this, &MainWindow::handelResult2);
}

MainWindow::~MainWindow()
{
    delete ui;


}
