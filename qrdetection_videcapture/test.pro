QT += core gui multimedia widgets multimediawidgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

HEADERS +=

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS +=-L"$$[QT_SYSROOT]/usr/lib" -lopencv_core  -lopencv_imgproc  -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lv4l2 -lopencv_highgui
LIBS += -L"$$[QT_SYSROOT]/usr/lib" -lzbar

INCLUDEPATH += "$$[QT_SYSROOT]/usr/include"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/rockx"
INCLUDEPATH += "$$[QT_SYSROOT]/usr/include/zbar"
