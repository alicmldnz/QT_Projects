#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCamera>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <qpushbutton.h>
#include <QCameraDevice>
#include <QMediaDevices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}

