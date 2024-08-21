#ifndef CAMERA_H
#define CAMERA_H


class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    virtual ~Camera();
};

#endif // CAMERA_H
