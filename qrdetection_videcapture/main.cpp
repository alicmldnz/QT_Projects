#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QVBoxLayout>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <iostream>
using namespace cv;
using namespace zbar;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a main widget
    QWidget mainWindow;
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    QLabel *imageLabel = new QLabel(&mainWindow);
    layout->addWidget(imageLabel);
    mainWindow.setLayout(layout);

    // Open the camera
    VideoCapture cap(1);
    if (!cap.isOpened()) {
        qFatal("Could not open the camera");
    }

    // Set camera resolution
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    // Set up a timer to process frames
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            qWarning("Empty frame captured");
            return;
        }

        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Initialize zbar scanner
        ImageScanner scanner;
        scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

        // Wrap OpenCV image in a zbar image
        Image zbarImage(frame.cols, frame.rows, "Y800", gray.data, frame.cols * frame.rows);

        // Scan the image for QR codes
        scanner.scan(zbarImage);

        for (Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
            QString myData = QString::fromStdString(symbol->get_data());
            std::cout << myData.toStdString() << std::endl;

            // Check if detected data is in the predefined list
            std::string allowedData = "111111";
            Scalar color = (myData.toStdString() == allowedData) ? Scalar(0, 255, 0) : Scalar(0, 0, 255);

            // Draw a polygon around the QR code
            std::vector<Point> points;
            for (int i = 0; i < symbol->get_location_size(); i++) {
                points.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
            }
            polylines(frame, points, true, color, 5);

            // Put text on the frame
            Rect rect = boundingRect(points);
            putText(frame, myData.toStdString(), Point(rect.x, rect.y), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);
        }

        // Display the resulting frame
        QImage qtImage = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        imageLabel->setPixmap(QPixmap::fromImage(qtImage));
    });

    timer.start(30);  // Adjust the interval as needed

    // Show the main window
    mainWindow.show();
    return app.exec();
}
