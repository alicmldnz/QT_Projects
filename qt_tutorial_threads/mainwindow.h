#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <mythread.h>
#include <QMainWindow>

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

    MyThread *mThread;

public slots:
    void onNumberChanged(int);

private slots:
    void start();
    void stop();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
