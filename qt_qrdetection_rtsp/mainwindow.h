#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "streamer.h"
#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVideoProbe *probe;
    QCamera *camera;
    Streamer *streamer;
public Q_SLOTS:
    void processFrame(const QVideoFrame &frame);
};

#endif // MAINWINDOW_H
