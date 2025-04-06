#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img = imread("messi5.jpg");

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Set the region of interest
    Mat img_ROI_01 = img(Rect(338, 286, 53, 47));
    Mat img_ROI_02 = img(Rect(Point(338, 286), Point(390, 332)));

    // Display the region of interest
    imshow("Ball 1", img_ROI_01);
    imshow("Ball 2", img_ROI_02);
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    // shallow vs. deep copy?
    if (img.data == img_ROI_01.data || img.data == img_ROI_01.datastart) 
        cout << "ROI: shallow copy" << endl;
    else
        cout << "ROI: deep copy" << endl;

    // double check
    img_ROI_01 = Scalar(0); // make the blue channel black

    // Display the region of interest
    imshow("Original Image", img);
    imshow("Ball 1", img_ROI_01);
    imshow("Ball 2", img_ROI_02);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}