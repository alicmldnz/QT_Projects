#ifndef STREAMER_H
#define STREAMER_H
#include <QThread>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <QMutex>



#include <QTimer>
#include <QElapsedTimer>


#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

class Streamer : public QObject
{
    Q_OBJECT
public:
    Streamer(QObject *parent = 0);
    static Streamer *VideoStreamer_ptr;


private:
    std::string TAG = "Streamer";
    GstElement *gst_pipeline;
    GstElement *gst_src;
    guint frame_number = 0;
    QTimer *streamTimer;

    GstElement *gst_element = nullptr;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;
    static void gst_need_data();
    static void gst_enough_data();
    static void gst_media_configure(GstRTSPMediaFactory *factory, GstRTSPMedia *media, gpointer user_data);
    static void clientConnected(GstRTSPServer *server, GstRTSPClient *client, gpointer user_data);
    static void clientClosed(GstRTSPClient *client, gpointer user_data);

    std::chrono::time_point<std::chrono::system_clock> start_time_control;
    std::chrono::time_point<std::chrono::system_clock> end_time_control;
    // std::chrono::duration<float> time_control;
    int push_gst_data(cv::Mat current_frame);
    static int clientCounter;
    bool gst_has_enough = false;
    QElapsedTimer *gst_timestamp_timer;
    QMutex mutex;
    cv::Mat lastFrame;
    void initRga();

Q_SIGNALS:
    void gst_start_timer(int);
    void gst_stop_timer();

public Q_SLOTS:
    void initStream();
    void streamFrame();
    void updateFrame(cv::Mat);
};

#endif // STREAMER_H
