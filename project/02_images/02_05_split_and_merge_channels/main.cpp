#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img_color = imread("RGB.png");

    // Check if image loading is successful
    if (img_color.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Split each color channel
    Mat img_BGR[3];
    split(img_color, img_BGR);

    // Merge all channels
    Mat img_merged;
    merge(img_BGR, 3, img_merged);

    // Display all channels in a window
    imshow("Original Image", img_color);
    imshow("R Channel", img_BGR[2]);
    imshow("G Channel", img_BGR[1]);
    imshow("B Channel", img_BGR[0]);
    imshow("Merged Channels", img_merged);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    // split: shallow vs. deep copy?
    if (img_color.data == img_BGR[0].data)
        cout << "Split: shallow copy" << endl;
    else
        cout << "Split: deep copy" << endl;

    // merge: shallow vs. deep copy?
    if (img_merged.data == img_BGR[0].data)
        cout << "Merge: shallow copy" << endl;
    else
        cout << "Merge: deep copy" << endl;

    // double check
    img_BGR[0] = Scalar(0); // make the blue channel black

    // Display all channels in a window
    imshow("Original Image", img_color);
    imshow("R Channel", img_BGR[2]);
    imshow("G Channel", img_BGR[1]);
    imshow("B Channel", img_BGR[0]);
    imshow("Merged Channels", img_merged);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();
    
    return 0;
}