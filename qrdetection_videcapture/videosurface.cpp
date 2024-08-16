// VideoSurface.cpp

#include "videosurface.h".h"
#include <QDebug>

VideoSurface::VideoSurface(QObject *parent)
    : QAbstractVideoSurface(parent) {
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const {
    Q_UNUSED(handleType);
    return { QVideoFrame::Format_RGB32, QVideoFrame::Format_ARGB32, QVideoFrame::Format_RGB24 };
}

bool VideoSurface::present(const QVideoFrame &frame) {
    if (!frame.isValid()) {
        return false;
    }

    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

    QImage image(
        cloneFrame.bits(),
        cloneFrame.width(),
        cloneFrame.height(),
        cloneFrame.bytesPerLine(),
        QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat())
        );

    if (image.isNull()) {
        qDebug() << "Failed to convert QVideoFrame to QImage";
        return false;
    }

    emit frameAvailable(image);
    cloneFrame.unmap();
    return true;
}
