#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a video capture object
    VideoCapture capture("vtest.avi");

    // Check if video loading is successful
    if (!capture.isOpened())
    {
        cerr << "Error: No video exists!" << endl;
        exit(-1);
    }

    // Infinite loop
    Mat frame;
    while (true)
    {
        // Read a video frame
        capture >> frame;

        // Check if frame capture is successful
        if (frame.empty()) break;

        // Display the frame in a window
        imshow("Video Frame", frame);

        // Take the keyboard input
        char key = waitKey(33);

        // Press ESC to quit
        if (key == 27) break;

        // Press Spacebar to pause
        if (key == 32)
        {
            key = waitKey(0);
            if (key == 27) break;
        }
    }

    // Release the capture object
    capture.release();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}