#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include "mythread.h"
#include "worker.h"
#include "controller.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myThread = new MyThread();
    connect(myThread, &MyThread::finished, myThread, &QObject::deleteLater);
    connect(myThread, &MyThread::resultReady, this, &MainWindow::handelResult);

    worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::startOperation, worker, &Worker::doWork2);
    connect(worker, &Worker::resultReady2, this, &MainWindow::handelResult2);

    coworker = new Worker;
    coworker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, coworker, &QObject::deleteLater);
    connect(this, &MainWindow::startOperation2, coworker, &Worker::doWork3);
    connect(coworker, &Worker::resultReady3, this, &MainWindow::handelResult3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    myThread->start();
}


void MainWindow::on_pushButton_2_clicked()
{

    ui-> label-> setText("message 1");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui-> label-> setText("message 2");
}


void MainWindow::on_pushButton_4_clicked()
{
    myThread->quit();
    myThread->exit();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString start;

    emit startOperation(start);
    workerThread.start();
}


void MainWindow::on_pushButton_6_clicked()
{
    QString start;

    emit startOperation2(start);
    workerThread.start();
}

void MainWindow::handelResult()
{

    ui-> label->setText("worked");
}
void MainWindow::handelResult2()
{

    ui-> label_2->setText("calistim");
}
void MainWindow::handelResult3()
{

    ui-> label_3->setText("yandan calistim");
}

