#include "camera.h"
#include <opencv2/opencv.hpp>
#include <zbar.h>
Camera::Camera(QObject *parent)
    : QObject{parent}
{

}

Camera::~Camera()
{
    camera->stop();
}

