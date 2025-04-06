#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a color image
    Mat img = imread("messi5.jpg");

    // Check if image loading is successful
    if (img.empty())
    {
        cerr << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Infinite loop
    bool quit = false;
    while (!quit)
    {
        // Display the image in a window
        imshow("Lionel Messi", img);
        
        // Wait for a key to be pressed
        char key = waitKey(1);

        // Flip the image
        switch (key)
        {
            // Flip aroun the x-axis: vertically
            case 'x':
            case 'X':
                flip(img, img, 0);
                break;
            
            // Flip aroun the y-axis: horizontally
            case 'y':
            case 'Y':
                flip(img, img, 1);
                break;
            
            // ESC
            case 27:
                quit = true;
                break;
        }
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}