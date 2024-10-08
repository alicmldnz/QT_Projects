#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "worker.h"
#include "controller.h"
#include <QMainWindow>
#include "mythread.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void startOperation(const QString &s);
    void startOperation2(const QString &s);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void handelResult();

    void handelResult2();

    void handelResult3();

private:
    Ui::MainWindow *ui;
    MyThread *myThread;
    Worker *worker;
    Worker *coworker;
};
#endif // MAINWINDOW_H
