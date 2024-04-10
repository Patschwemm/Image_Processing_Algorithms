// Image_Processing_Algorithms.cpp : Defines the entry point for the application.

#include "Image_Processing_Algorithms.h"
#include <opencv2/opencv.hpp>
#include <utils.h>
#include <color/grayscale.h>
#include <geometry/flip.h>
#include <geometry/resize.h>

int main() {

    cv::Mat image = readLena("rgb");

    std::cout << image.rows << " rows, "
        << image.cols << " cols, "
        << image.size().width << "x" << image.size().height << ", "
        << image.channels() << "channels, "
        << image.type() << " type" << std::endl;

    std::cout << type2str(image.type()) << std::endl;

    // to track time
    ExecutionTimer timer = ExecutionTimer();

    timer.startClock();
    cv::Mat nearestMat = nearestInterpolation(image, 700, 700);
    timer.endClock("Resize neasrest");
    timer.startClock();
    cv::Mat bilinearMat = bilinearInterpolation(image, 700, 700);
    timer.endClock("Resize bilinear");

    // Display the original and grayscale images
    cv::imshow("Original Image", image);
    cv::imshow("Resized Nearest Image", nearestMat);
    cv::imshow("Resized Bilinear Image", bilinearMat);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}