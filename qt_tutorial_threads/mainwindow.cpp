#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mThread = new MyThread(this);
    connect(mThread,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onNumberChanged(int Number)
{
    ui->label->setText(QString::number(Number));
}
void MainWindow::start()
{
    mThread->start();
}


void MainWindow::stop()
{
    mThread->Stop =true;
}

