#include "capturer.h"
#include <QThread>

Capturer::Capturer(QObject *parent)
    : QObject{parent} {}

Capturer::~Capturer()
{
    if (camera) {
        camera->stop();
        delete camera;
    }
    if (probe) {
        delete probe;
    }
}

void Capturer::start()
{
    probe = new QVideoProbe;
    camera = new QCamera(QCamera::availableDevices().at(1));
    probe->setSource(camera);
    camera-> start();
    // qDebug() << "camera has started" << QThread::currentThreadId();
    connect(probe, &QVideoProbe::videoFrameProbed, this, &Capturer::frameReady);
}
