#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <QGuiApplication>
#include <QImage>
#include <QPixmap>
#include <QFile>
#include <QDebug>

using namespace cv;
using namespace std;
using namespace zbar;

typedef struct
{
    string type;
    string data;
    vector<Point> location;
} decodedObject;

// Find and decode barcodes and QR codes
void decode(Mat &im, vector<decodedObject>& decodedObjects)
{
    // Create zbar scanner
    ImageScanner scanner;

    // Configure scanner
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray;
    cvtColor(im, imGray, COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    // Print results
    // Detect Control
    // if ( n>1)
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        qDebug() << "Type :" << QString::fromStdString(obj.type);
        qDebug() << "Data :" << QString::fromStdString(obj.data);

        // Obtain location
        for (int i = 0; i < symbol->get_location_size(); i++)
        {
            obj.location.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
        }

        decodedObjects.push_back(obj);
    }
}

// Display results with a specified window size
void display(Mat &im, vector<decodedObject>& decodedObjects)
{
    // Loop over all decoded objects
    for (int i = 0; i < decodedObjects.size(); i++)
    {
        vector<Point> points = decodedObjects[i].location;
        vector<Point> hull;

        // If the points do not form a quad, find convex hull
        if (points.size() > 4)
            convexHull(points, hull);
        else
            hull = points;

        // Number of points in the convex hull
        int n = hull.size();

        for (int j = 0; j < n; j++)
        {
            line(im, hull[j], hull[(j + 1) % n], Scalar(255, 0, 0), 3);
        }
    }

    // Convert Mat to QImage
    QImage qimg(im.data, im.cols, im.rows, im.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimg.rgbSwapped());

    // Save the processed image
    QString baseName = "IMG_00000037"; // Example base name
    QString resultPath = baseName + "_result.jpg";
    pixmap.save(resultPath);

    qDebug() << "Saved processed image to" << resultPath;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv); // Changed to QGuiApplication

    // Read image
    Mat im = imread("/opt/ali/IMG_00000037.jpg");

    // Variable for decoded objects
    vector<decodedObject> decodedObjects;

    // Find and decode barcodes and QR codes
    decode(im, decodedObjects);

    // Display location
    display(im, decodedObjects);

    return EXIT_SUCCESS;
}
