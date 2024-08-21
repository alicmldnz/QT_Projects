QT += core  multimedia widgets

CONFIG += c++17 cmdline

CONFIG += no_keywords
CONFIG -= app_bundle
CONFIG += qt
CONFIG += link_pkgconfig
packagesExist(gstreamer-1.0) {
    PKGCONFIG   += gstreamer-1.0
}
packagesExist(gstreamer-rtsp-server-1.0) {
    PKGCONFIG   += gstreamer-rtsp-server-1.0
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        streamer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mainwindow.h \
    streamer.h


LIBS +=-L"$$[QT_SYSROOT]/usr/lib" -lopencv_core  -lopencv_imgproc  -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lv4l2 -lopencv_highgui

LIBS += -L"$$[QT_SYSROOT]/usr/lib" -lzbar -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
LIBS += -L"$$[QT_SYSROOT]/usr/lib" -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
LIBS += -L"$$[QT_SYSROOT]/usr/lib" -lzbar

INCLUDEPATH += "$$[QT_SYSROOT]/usr/include"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/rockx"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/gstreamer-1.0"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/glib-2.0"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/zbar"

FORMS += \
    mainwindow.ui


