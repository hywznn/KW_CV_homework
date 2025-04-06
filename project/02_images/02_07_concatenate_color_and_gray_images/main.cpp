#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img_color = imread("messi5.jpg", IMREAD_COLOR);

    // Check if image loading is successful
    if (img_color.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Convert the color image to gray
    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    // Convert the gray to color image
    Mat img_gray_3channels;
    cvtColor(img_gray, img_gray_3channels, COLOR_GRAY2BGR);

    // Concatenate color and gray images
    Mat img_color_vs_gray;
    hconcat(img_color, img_gray_3channels, img_color_vs_gray);

    // Display both images in a single window
    imshow("Color vs Gray Images", img_color_vs_gray);
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}