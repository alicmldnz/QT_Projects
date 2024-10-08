#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QImage>

class VideoSurface : public QAbstractVideoSurface {
    Q_OBJECT
public:
    explicit VideoSurface(QObject *parent = nullptr);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const override;
    bool present(const QVideoFrame &frame) override;

signals:
    void frameAvailable(const QImage &image);
};

#endif // VIDEOSURFACE_H
