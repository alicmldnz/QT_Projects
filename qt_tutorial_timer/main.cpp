#include "mainwindow.h"
#include "mytimer.h"
#include <QApplication>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTimer mTimer;
    return a.exec();
}
