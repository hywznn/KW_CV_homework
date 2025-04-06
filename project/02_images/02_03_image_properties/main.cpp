#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image in a grayscale
    Mat img = imread("messi5.jpg", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Image properties
    cout << "Image width: "  << img.cols << endl;
    cout << "Image height: " << img.rows << endl;
    cout << "Image channles: " << img.channels() << endl;
    switch (img.depth())
    {
        case CV_8U:  cout << "CV_8U"   << endl; break;  // 0
        case CV_8S:  cout << "CV_8S"   << endl; break;  // 1
        case CV_16U: cout << "CV_16U"  << endl; break;  // 2
        case CV_16S: cout << "CV_16S"  << endl; break;  // 3
        case CV_32S: cout << "CV_32S"  << endl; break;  // 4
        case CV_32F: cout << "CV_32F"  << endl; break;  // 5
        case CV_64F: cout << "CV_64F"  << endl; break;  // 6
        case CV_16F: cout << "CV_16F"  << endl; break;  // 7
    }

    // OpenCV image type: image depth + channels
    switch (img.type())
    {
        case CV_8UC1: cout << "CV_8UC1" << endl; break;
        case CV_8UC2: cout << "CV_8UC2" << endl; break;
        case CV_8UC3: cout << "CV_8UC3" << endl; break;
        case CV_8UC4: cout << "CV_8UC4" << endl; break;

        case CV_8SC1: cout << "CV_8SC1" << endl; break;
        case CV_8SC2: cout << "CV_8SC2" << endl; break;
        case CV_8SC3: cout << "CV_8SC3" << endl; break;
        case CV_8SC4: cout << "CV_8SC4" << endl; break;

        case CV_16UC1: cout << "CV_16UC1" << endl; break;
        case CV_16UC2: cout << "CV_16UC2" << endl; break;
        case CV_16UC3: cout << "CV_16UC3" << endl; break;
        case CV_16UC4: cout << "CV_16UC4" << endl; break;

        case CV_16SC1: cout << "CV_16SC1" << endl; break;
        case CV_16SC2: cout << "CV_16SC2" << endl; break;
        case CV_16SC3: cout << "CV_16SC3" << endl; break;
        case CV_16SC4: cout << "CV_16SC4" << endl; break;

        case CV_32SC1: cout << "CV_32SC1" << endl; break;
        case CV_32SC2: cout << "CV_32SC2" << endl; break;
        case CV_32SC3: cout << "CV_32SC3" << endl; break;
        case CV_32SC4: cout << "CV_32SC4" << endl; break;

        case CV_32FC1: cout << "CV_32FC1" << endl; break;
        case CV_32FC2: cout << "CV_32FC2" << endl; break;
        case CV_32FC3: cout << "CV_32FC3" << endl; break;
        case CV_32FC4: cout << "CV_32FC4" << endl; break;

        case CV_64FC1: cout << "CV_64FC1" << endl; break;
        case CV_64FC2: cout << "CV_64FC2" << endl; break;
        case CV_64FC3: cout << "CV_64FC3" << endl; break;
        case CV_64FC4: cout << "CV_64FC4" << endl; break;
        
        case CV_16FC1: cout << "CV_16FC1" << endl; break;
        case CV_16FC2: cout << "CV_16FC2" << endl; break;
        case CV_16FC3: cout << "CV_16FC3" << endl; break;
        case CV_16FC4: cout << "CV_16FC4" << endl; break;
    }

    return 0;
}