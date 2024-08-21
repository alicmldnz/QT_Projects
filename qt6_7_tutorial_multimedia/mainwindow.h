#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaCaptureSession>
#include <QMainWindow>
#include <QVideoSink>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QCamera>
#include <QScopedPointer>

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


private slots:


private:
    Ui::MainWindow *ui;
    QScopedPointer<QCamera> *camera;
};
#endif // MAINWINDOW_H
