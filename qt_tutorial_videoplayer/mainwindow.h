#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QSlider>
#include <QProgressBar>
#include <QAudioOutput>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QSlider* slider;
    QProgressBar* bar;
    QAudioOutput* audio;
private slots:
    void on_actionplay_triggered();
    void on_actionstop_triggered();
    void on_actionpause_triggered();
    void on_actionOpen_triggered();
};
#endif // MAINWINDOW_H
