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

    // Get the image size
    int nChannels = imgColor.channels();
    int nRows = imgColor.rows;
    int nCols = imgColor.cols;
    
    // Start the stop watch
    double t = (double)getTickCount();

    // Iterate over the whole image
    uchar *pImgColor, *pImgResult;
    for (int row = 0; row < nRows; ++row)
    {
        pImgColor  = imgColor.ptr<uchar>(row);
        pImgResult = imgResult.ptr<uchar>(row);
        for (int col = 0; col < nCols; ++col)
        {
            // Read the pixel from the color image
            uchar B = pImgColor[nChannels*col + 0];
            uchar G = pImgColor[nChannels*col + 1];
            uchar R = pImgColor[nChannels*col + 2];

            // Convert it to gray
            uchar gray = uchar(0.299*R + 0.587*G + 0.114*B);

            // Write the pixel to the gray image
            pImgResult[nChannels*col + 0] = gray;
            pImgResult[nChannels*col + 1] = gray;
            pImgResult[nChannels*col + 2] = gray;
        }
    }

    // Remove the ball area
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