#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "streamer.h"
#include "capturer.h"
#include "detection.h"
#include "convert.h"
#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread capturerThread, detectionThread, streamerThread, convertThread;
    bool *flag;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void StartCapturer();
    void StartStreamer();
    void StartDetection();
    void StartConvert();

private:
    Ui::MainWindow *ui;
    Streamer *streamer;
    Capturer *capturer;
    Detection *detection;
    Convert *convert;
public Q_SLOTS:
    void signalControllerFlag();
Q_SIGNALS:
    void operate();

};

#endif // MAINWINDOW_H
