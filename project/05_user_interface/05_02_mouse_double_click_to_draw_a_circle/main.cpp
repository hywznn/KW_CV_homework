#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Image
Mat g_imgColor;

// OpenCV Random Number Generator
RNG g_rng(getTickCount());
Scalar randomColor(RNG &g_rng)
{
    int icolor = (unsigned) g_rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

// Mouse callback function
void mouse_callback(int event, int x, int y, int flags, void *param)
{
    // Left button double clicked
    if (event == EVENT_LBUTTONDBLCLK)
    {
        // Pick a random radius
        int radius = g_rng.uniform(10, 50);

        // Pick a random color
        Scalar color = randomColor(g_rng);

        // Draw a circle
        circle(g_imgColor, Point(x, y), radius, color, -1);
    }
}

int main()
{
    // Create a black image
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);

    // Create a window
    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // Register the mouse callback function
    setMouseCallback(strWindowName, mouse_callback);

    // Infinite loop
    while (true)
    {
        // Display the image
        imshow(strWindowName, g_imgColor);

        // Get user input
        char key = waitKey(1);

        // ESC
        if (key == 27) break;
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}