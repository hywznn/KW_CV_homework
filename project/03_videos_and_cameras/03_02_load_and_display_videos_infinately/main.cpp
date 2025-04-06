#include <iostream>
#include <string>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a video capture object
    String videoName = "vtest.avi";
    VideoCapture capture(videoName.c_str());

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
        char key = waitKey(1);

        // Press ESC to quit
        if (key == 27) break;

        // Press Spacebar to pause
        if (key == 32)
        {
            key = waitKey(0);
            if (key == 27) break;
        }

        // Repeat the video
        if (capture.get(CAP_PROP_POS_FRAMES) == capture.get(CAP_PROP_FRAME_COUNT))
            capture.open(videoName.c_str());
    }

    // Release the capture object
    capture.release();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}