#include "streamer.h"
#include <QDebug>
#include <unistd.h>
Streamer *Streamer::VideoStreamer_ptr = nullptr;
int Streamer::clientCounter = 0;
const int STREAM_WIDTH = 1280;
const int STREAM_HEIGHT = 720;
Streamer::Streamer(QObject *parent) : QObject(parent)
{
    VideoStreamer_ptr = this;
    streamTimer = new QTimer(this);
    connect(streamTimer, &QTimer::timeout, this, &Streamer::streamFrame);
    //initStream();
    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] Streamer construct done");
}

void Streamer::initStream()
{
    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] Streamer init started");

    clientCounter = 0;

    streamTimer->start(40);
    gst_init(NULL, NULL);
    gst_timestamp_timer = new QElapsedTimer();

    // if (c_RkRgaInit() < 0)
    // {
    //     logger(TAG, -1, "RkRga couldn't init in Streamer");
    //     return;
    // }

    /* create a server instance */
    server = gst_rtsp_server_new();

    /* get the mount points for this server, every server has a default object
     * that be used to map uri mount points to media factories */
    mounts = gst_rtsp_server_get_mount_points(server);

    /* make a media factory for a test stream. The default media factory can use
     * gst-launch syntax to create pipelines.
     * any launch line works as long as it contains elements named pay%d. Each
     * element with pay%d names will be a stream */
    factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory,
                                      "( appsrc name=gst_src ! queue max-size-buffers=2 !  mpph264enc header-mode=1 profile=66 level=31 gop=50 ! h264parse  ! rtph264pay name=pay0 pt=96 )");
    gst_rtsp_media_factory_set_shared(factory, true);
    /* notify when our media is ready, This is called whenever someone asks for
     * the media and a new pipeline with our appsrc is created */
    g_signal_connect(factory, "media-configure", (GCallback)Streamer::gst_media_configure,
                     NULL);
    g_signal_connect(server, "client-connected", (GCallback)clientConnected,
                     NULL);
    // logger(TAG, "started");

    /* attach the test factory to the /test url */
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);

    /* attach the server to the default maincontext */
    gst_rtsp_server_attach(server, NULL);
    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] Streamer init done");

}

// void Streamer::initRga()
// {
//     rgaCopy = RgaCreate();
//     if (rgaCopy == nullptr)
//     {
//         logger(TAG, -1, "Rga copier couldn't init in Streamer");
//         return;
//     }
//     rgaCopy->ops->initCtx(rgaCopy);
//     // rgaStream->ops->setRotate(rgaStream, ROTATE_RGA_STREAM_DTSIS);

//     rgaCopy->ops->setSrcFormat(rgaCopy, V4L2_PIX_FMT_RGB24, STREAM_WIDTH, STREAM_HEIGHT);
//     rgaCopy->ops->setDstFormat(rgaCopy, V4L2_PIX_FMT_RGB24, STREAM_WIDTH, STREAM_HEIGHT);

//     //    lastFrame.create(cv::Size(STREAM_WIDTH, STREAM_HEIGHT), CV_8UC3);

//     //    rgaCopy->ops->setDstBufferPtr(rgaCopy, lastFrame.data);

//     rgaStream = RgaCreate();
//     if (rgaStream == nullptr)
//     {
//         logger(TAG, -1, "Rga streamer couldn't init in Streamer");
//         return;
//     }
//     rgaStream->ops->initCtx(rgaStream);
//     // rgaStream->ops->setRotate(rgaStream, ROTATE_RGA_STREAM_DTSIS);

//     rgaStream->ops->setSrcFormat(rgaStream, V4L2_PIX_FMT_RGB24, STREAM_WIDTH, STREAM_HEIGHT);
//     rgaStream->ops->setDstFormat(rgaStream, V4L2_PIX_FMT_NV12, STREAM_WIDTH, STREAM_HEIGHT);
//     logger(TAG, "Stream RGA init done");
//}

void Streamer::gst_media_configure(GstRTSPMediaFactory *factory, GstRTSPMedia *media, gpointer user_data)
{

    /* get the element used for providing the streams of the media */
    VideoStreamer_ptr->gst_element = gst_rtsp_media_get_element(media);

    /* get our appsrc, we named it 'mysrc' with the name property */
    VideoStreamer_ptr->gst_src = gst_bin_get_by_name_recurse_up(GST_BIN(VideoStreamer_ptr->gst_element), "gst_src");

    // examine this carefully later and decide if we will use it -------------------------------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //    /* this instructs appsrc that we will be dealing with timed buffer */
    //    gst_util_set_object_arg (G_OBJECT (appsrc), "format", "time");

    g_object_set(G_OBJECT(VideoStreamer_ptr->gst_src), "caps",
                 gst_caps_new_simple("video/x-raw",
                                     "format", G_TYPE_STRING, "NV12",
                                     "width", G_TYPE_INT, STREAM_WIDTH,
                                     "height", G_TYPE_INT, STREAM_HEIGHT,
                                     "framerate", GST_TYPE_FRACTION, 25, 1,
                                     NULL),
                 NULL);

    // g_object_set (G_OBJECT (gst_src), "max-buffers", 1);

    g_object_set(G_OBJECT(VideoStreamer_ptr->gst_src),
                 "stream-type", 0,
                 "is-live", TRUE,
                 "format", GST_FORMAT_TIME,
                 nullptr);

    g_signal_connect(VideoStreamer_ptr->gst_src, "need-data", G_CALLBACK(Streamer::gst_need_data), NULL);
    g_signal_connect(VideoStreamer_ptr->gst_src, "enough-data", G_CALLBACK(Streamer::gst_enough_data), NULL);

    qInfo() << "stream ready at rtsp://127.0.0.1:8554/test\n";

    VideoStreamer_ptr->gst_timestamp_timer->start();
}

void Streamer::gst_need_data()
{
    // qDebug() << "GST Needs Data";
    // logger("Streamer", "GST Needs Data");
    VideoStreamer_ptr->gst_has_enough = false;
    // VideoStreamer_ptr->streamFrame();
}

void Streamer::gst_enough_data()
{
    // qDebug() << "GST Has Enough Data";
    VideoStreamer_ptr->gst_has_enough = true;
}

// int Streamer::push_gst_data(cv::Mat current_frame)
// {
//     auto start_time_rga = std::chrono::high_resolution_clock::now();

//     cv::Mat current_frame_NV12;
//     current_frame_NV12.create(cv::Size(STREAM_WIDTH, STREAM_HEIGHT * 3 / 2), CV_8UC1);

//     rgaStream->ops->setSrcBufferPtr(rgaStream, current_frame.data);
//     rgaStream->ops->setDstBufferPtr(rgaStream, current_frame_NV12.data);

//     int ret_rga;
//     auto start_time_go = std::chrono::high_resolution_clock::now();
//     ret_rga = rgaStream->ops->go(rgaStream);
//     auto end_time_go = std::chrono::high_resolution_clock::now();
//     auto time_go = chrono::duration_cast<chrono::milliseconds>(end_time_go - start_time_go).count();
//     if (LOG_TIME)
//         logger(TAG, "[ TIME ] Streamer RGA go: " + to_string(time_go) + " ms");

//     if (ret_rga < 0)
//     {
//         logger(TAG, -1, "Rga stream failed");
//         return -1;
//     }

//     auto end_time_rga = std::chrono::high_resolution_clock::now();
//     auto time_rga = chrono::duration_cast<chrono::milliseconds>(end_time_rga - start_time_rga).count();
//     if (LOG_TIME)
//         logger(TAG, "[ TIME ] Streamer RGA time: " + to_string(time_rga) + " ms");

//     GstBuffer *buffer;
//     GstMemory *memory;
//     GstMapInfo map;
//     GstFlowReturn ret_gst;

//     buffer = gst_buffer_new();

//     memory = gst_memory_new_wrapped((GstMemoryFlags)0, (gpointer)current_frame_NV12.data, (current_frame_NV12.cols * current_frame_NV12.rows), 0, (current_frame_NV12.rows * current_frame_NV12.cols), NULL, NULL);

//     gst_buffer_insert_memory(buffer, -1, memory);

//     GST_BUFFER_PTS(buffer) = gst_timestamp_timer->nsecsElapsed();

//     //  qDebug() << "gst_src: "<<gst_src->base_time;
//     g_signal_emit_by_name(gst_src, "push-buffer", buffer, &ret_gst);

//     gst_buffer_unref(buffer);
//     if (ret_gst != GST_FLOW_OK)
//         return -1;

//     if (LOG_DETAILS)
//         logger(TAG, "[DETAIL] gst pushed data successfully");


//     return 0;
// }
int Streamer::push_gst_data(cv::Mat current_frame)
{
    auto start_time_opencv = std::chrono::high_resolution_clock::now();

    cv::Mat current_frame_NV12;
    cv::cvtColor(current_frame, current_frame_NV12, cv::COLOR_RGB2YUV_I420);

    // if (current_frame_NV12.empty())
    // {
    //     logger(TAG, -1, "OpenCV conversion failed");
    //     return -1;
    // }

    GstBuffer *buffer;
    GstMemory *memory;
    GstMapInfo map;
    GstFlowReturn ret_gst;

    buffer = gst_buffer_new();

    memory = gst_memory_new_wrapped((GstMemoryFlags)0, (gpointer)current_frame_NV12.data, (current_frame_NV12.cols * current_frame_NV12.rows * 3 / 2), 0, (current_frame_NV12.rows * current_frame_NV12.cols * 3 / 2), NULL, NULL);

    gst_buffer_insert_memory(buffer, -1, memory);

    GST_BUFFER_PTS(buffer) = gst_timestamp_timer->nsecsElapsed();

    g_signal_emit_by_name(gst_src, "push-buffer", buffer, &ret_gst);

    gst_buffer_unref(buffer);
    if (ret_gst != GST_FLOW_OK)
        return -1;

    auto end_time_opencv = std::chrono::high_resolution_clock::now();
    auto time_opencv = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_opencv - start_time_opencv).count();
    // if (LOG_TIME)
    //     logger(TAG, "[ TIME ] Streamer OpenCV time: " + std::to_string(time_opencv) + " ms");

    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] gst pushed data successfully");

    return 0;
}


// void Streamer::updateFrame(cv::Mat newFrame)
// {
//     if (LOG_DETAILS)
//         logger(TAG, "[DETAIL] updateFrame " +to_string(clientCounter));


//     rgaCopy->ops->setSrcBufferPtr(rgaCopy, newFrame.data);

//     mutex.lock();
//     // not sure if create and setDst must be here, check again
//     lastFrame.create(cv::Size(STREAM_WIDTH, STREAM_HEIGHT), CV_8UC3);
//     rgaCopy->ops->setDstBufferPtr(rgaCopy, lastFrame.data);
//     auto ret = rgaCopy->ops->go(rgaCopy);
//     mutex.unlock();
//     if (LOG_DETAILS)
//         logger(TAG, "[DETAIL] updateFrame");

//     if (ret < 0)
//     {
//         logger(TAG, -1, "rga copy error");
//         return;
//     }
// }
void Streamer::updateFrame(cv::Mat newFrame)
{
    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] updateFrame " + std::to_string(clientCounter));

    cv::Mat tempFrame;
    cv::cvtColor(newFrame, tempFrame, cv::COLOR_RGB2BGR); //Burası RGB2RGB olabilir'

    mutex.lock();
    lastFrame.create(cv::Size(STREAM_WIDTH, STREAM_HEIGHT), CV_8UC3);
    cv::resize(tempFrame, lastFrame, cv::Size(STREAM_WIDTH, STREAM_HEIGHT));
    mutex.unlock();

    // if (LOG_DETAILS)
    //     logger(TAG, "[DETAIL] updateFrame");
}

void Streamer::streamFrame()
{
    if (gst_has_enough)
    {
        return; // a little control mechanism, could be improved to something more sophisticated
    }

    if (VideoStreamer_ptr->gst_element != nullptr && clientCounter > 0)
    // if (VideoStreamer_ptr->gst_element != nullptr)
    {
        auto start_time_push = std::chrono::high_resolution_clock::now();
        mutex.lock();
        int ret = push_gst_data(lastFrame);
        mutex.unlock();
        // auto end_time_push = std::chrono::high_resolution_clock::now();
        //auto time_push = chrono::duration_cast<chrono::milliseconds>(end_time_push - start_time_push).count();

        // if (LOG_TIME)
        //     logger(TAG, "[ TIME ] Streamer push: " + to_string(time_push) + " ms");

        // if (ret < 0)
        // {
        //     qCritical() << "Gst pipeline push data failed!";
        // }
    }
}

void Streamer::clientClosed(GstRTSPClient *client, gpointer user_data)
{
    clientCounter--;
    // if (LOG_DETAILS)
    //     qDebug() << "Client left, current client count: " << clientCounter;
}

void Streamer::clientConnected(GstRTSPServer *server, GstRTSPClient *client, gpointer user_data)
{
    clientCounter++;
    g_signal_connect(client, "closed", (GCallback)clientClosed, NULL);
    // if (LOG_DETAILS)
    //     qDebug() << "New client, current client count: " << clientCounter;
}
