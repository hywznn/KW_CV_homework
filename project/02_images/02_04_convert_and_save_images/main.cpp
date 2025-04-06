#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img_bw = imread("messi5.jpg", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_bw.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Convert the color image to gray
    Mat img_color;
    cvtColor(img_bw, img_color, COLOR_GRAY2BGR);

    // Save the gray image
    imwrite("messi5_gray.jpg", img_color);
    
    // Display both images in each window
    imshow("Color Image", img_color);
    imshow("Gray Image", img_bw);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}