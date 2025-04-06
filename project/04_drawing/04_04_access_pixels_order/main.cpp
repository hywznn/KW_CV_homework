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
    int nRows = imgColor.rows;
    int nCols = imgColor.cols;

    // Start the stop watch
    double t = (double)getTickCount();

    // Iterate over the whole image
    for (int col = 0; col < nCols; col++)
    {
        for (int row = 0; row < nRows; row++)
        {
            // Read the pixel from the color image
            Vec3b &color = imgColor.at<Vec3b>(row, col);

            // Convert it to gray
            uchar gray = uchar(0.299*color[2] + 0.587*color[1] + 0.114*color[0]);

            // Write the pixel to the gray image
            imgResult.at<Vec3b>(row, col) = Vec3b(gray, gray, gray);
        }
    }

    // Remove the ball area
    for (int col = 338; col < 390; col++)
    {
        for (int row = 286; row < 332; row++)
        {
            // Write the pixel in the result image
            imgResult.at<Vec3b>(row, col) = Vec3b(0, 255, 0); // green
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