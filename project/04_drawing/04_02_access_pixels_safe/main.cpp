#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a color image
    Mat imgColor = imread("messi5.jpg");

    // Check if image loading is successful
    if (imgColor.empty())
    {
        cerr << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Create a color image with the same size and type
    Mat imgResult(imgColor.size(), imgColor.type());

    // Set the iterators
    MatIterator_<Vec3b> iterColor     = imgColor.begin<Vec3b>();
    MatIterator_<Vec3b> iterColorEnd  = imgColor.end<Vec3b>();
    MatIterator_<Vec3b> iterResult    = imgResult.begin<Vec3b>();
    MatIterator_<Vec3b> iterResultEnd = imgResult.end<Vec3b>();

    // Start the stop watch
    double t = (double)getTickCount();

    // Iterate over the whole image
    for(; iterColor != iterColorEnd; ++iterColor, ++iterResult)
    {
        // Read the pixel from the color image
        uchar B = (*iterColor)[0];
        uchar G = (*iterColor)[1];
        uchar R = (*iterColor)[2];

        // Convert it to gray
        uchar gray = uchar(0.299*R + 0.587*G + 0.114*B);

        // Write the pixel to the gray image
        (*iterResult)[0] = gray;
        (*iterResult)[1] = gray;
        (*iterResult)[2] = gray;
    }

    // Remove the ball area
    int nChannels = imgColor.channels();
    uchar *pImgResult;
    for (int row = 286; row < 332; row++)
    {
        pImgResult = imgResult.ptr<uchar>(row);
        for (int col = 338; col < 390; col++)
        {
            // Write the pixel in the result image
            pImgResult[nChannels*col + 0] = 0;
            pImgResult[nChannels*col + 1] = 255; // green
            pImgResult[nChannels*col + 2] = 0;
        }
    }

    // Stop the stop watch
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    cout << t << " miliseconds" << endl;

    // Concatenate the images
    Mat imgDisplay;
    hconcat(imgColor, imgResult, imgDisplay);

    // Display the image in a window
    imshow("Access Pixels", imgDisplay);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}