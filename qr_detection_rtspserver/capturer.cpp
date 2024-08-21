#include "capturer.h"

Capturer::Capturer() {}

void Capturer::capture() {
    probe = new QVideoProbe;
    camera = new QCamera(QCamera::availableDevices().at(1));
    // Connect the videoFrameProbed signal to the processFrame slot
    bool connected = QObject::connect(probe, &QVideoProbe::videoFrameProbed, this, [this](const QVideoFrame &frame) {
        this->processFrame(frame);
    });
    if (!connected) {
        qDebug() << "Failed to connect videoFrameProbed signal to processFrame slot.";
    } else {
        qDebug() << "Signal-slot connection established.";
    }
    probe->setSource(camera);

    camera->start();
    qDebug() << "camera has started";
}





void Capturer::stopCam() {
    camera->stop();
}

