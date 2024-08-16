#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
public slots:

    void processFrame(const QVideoFrame &frame);
};

#endif // MAINWINDOW_H
