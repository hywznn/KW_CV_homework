#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a video capture object
    VideoCapture capture(0);

    // Check if camera loading is successful
    if (!capture.isOpened())
    {
        cerr << "Error: No camera exists!" << endl;
        exit(-1);
    }

    // Infinite loop
    Mat frame, flipped_frame;
    while (true)
    {
        // Read a video frame
        capture >> frame;

        // Check if frame capture is successful
        if (frame.empty()) break;

        // Flip the image horizontally
        flip(frame, flipped_frame, 1);

        // Display the frame in a window
        imshow("Video Frame", flipped_frame);

        // Take the keyboard input
        char key = waitKey(1);

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