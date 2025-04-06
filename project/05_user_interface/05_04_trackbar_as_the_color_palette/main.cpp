#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Trackbar callback function
void do_nothing(int pos, void *param)
{
}

int main()
{
    // Create a black image
    const int rows = 480;
    const int cols = 640;
    Mat imgColor = Mat::zeros(rows, cols, CV_8UC3);

    // Create a window
    String strWindowName = "Trackbar as the Color Palette";
    namedWindow(strWindowName);

    // Create trackbars for color change
    createTrackbar("R", strWindowName, 0, 255, do_nothing);
    createTrackbar("G", strWindowName, 0, 255, do_nothing);
    createTrackbar("B", strWindowName, 0, 255, do_nothing);

    // create switch for ON/OFF functionality
    String strSwitch = "0 : OFF \n1 : ON";
    createTrackbar(strSwitch, strWindowName, 0, 1, do_nothing);

    // Infinite loop
    while (true)
    {
        // Display the image
        imshow(strWindowName, imgColor);

        // Get user input
        char key = waitKey(1);

        // ESC
        if (key == 27) break;

        // Get current positions of four trackbars
        int R = getTrackbarPos("R", strWindowName);
        int G = getTrackbarPos("G", strWindowName);
        int B = getTrackbarPos("B", strWindowName);
        int S = getTrackbarPos(strSwitch, strWindowName);

        // Switch off: black, on: color
        if (S == 0) imgColor = Scalar(0, 0, 0); // black
        else        imgColor = Scalar(B, G, R); // RGB colors
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}