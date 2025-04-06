#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a black color image
    Mat img = Mat::zeros(480, 640, CV_8UC3);

    // Draw a line
    line(img, Point(0, 0), Point(200, 100), Scalar(0, 0, 255), 5);

    // Draw a rectangle
    rectangle(img, Point(300, 200), Point(500, 400), Scalar(0, 255, 0), 3);

    // Draw a circle
    circle(img, Point(100, 300), 40, CV_RGB(255, 255, 0), -1);

    // Draw an ellipse
    ellipse(img, Point(500, 300), Point(100, 50), 0, 0, 180, CV_RGB(0, 0, 255), -1);

    // Draw a polygon
    vector<Point> pts = {{100, 50}, {200, 300}, {600, 200}, {500, 100}};
    polylines(img, pts, true, CV_RGB(255, 0, 255) , 4);

    // Add a text
    int font = FONT_HERSHEY_SIMPLEX;
    putText(img, "OpenCV", Point(10, 450), font, 4, CV_RGB(255, 255, 255), 2, LINE_AA);

    // Display the image in a window
    imshow("Drawing", img);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}