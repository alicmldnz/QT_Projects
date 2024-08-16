#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vw = new QVideoWidget(this);
    player = new QMediaPlayer(this);
    audio = new QAudioOutput(this);

    player-> setVideoOutput(vw);
    this->setCentralWidget(vw);

    player-> setAudioOutput(audio);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);

    bar = new QProgressBar(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(on_actionOpen_triggered()));
    connect(ui->actionplay,SIGNAL(triggered(bool)),this,SLOT(on_actionplay_triggered()));
    connect(ui->actionpause,SIGNAL(triggered(bool)),this,SLOT(on_actionpause_triggered()));
    connect(ui->actionstop,SIGNAL(triggered(bool)),this,SLOT(on_actionstop_triggered()));


    ui->statusbar->addWidget(slider);
    ui->statusbar->addWidget(bar);


    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "open a file","","Video File(*.mp4)");
    on_actionstop_triggered();

    player->setSource(QUrl::fromLocalFile(filename));

    on_actionplay_triggered();
}


void MainWindow::on_actionstop_triggered()
{
    player->stop();

}


void MainWindow::on_actionpause_triggered()
{
    player-> pause();
}


void MainWindow::on_actionplay_triggered()
{
    player-> play();

}

