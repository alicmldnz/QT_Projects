#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "streamer.h"
#include "capturer.h"
#include "detection.h"
#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Streamer *streamer;
    Detection *detection;
    Capturer *capturer;
public Q_SLOTS:
    void processFrame(const QVideoFrame &frame);

Q_SIGNALS:
    void startOperation();
};

#endif // MAINWINDOW_H
