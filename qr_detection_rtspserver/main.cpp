#include <QApplication>
#include "mainwindow.h"
#include "streamer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Streamer streamer;
    MainWindow window;



    return a.exec();
}
