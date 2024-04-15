// Image_Processing_Algorithms.cpp : Defines the entry point for the application.

#include "Image_Processing_Algorithms.h"
#include <opencv2/opencv.hpp>
#include <utils.h>
#include <color/grayscale.h>
#include <geometry/flip.h>
#include <geometry/resize.h>
#include <filter/filter_alg.h>
#include <color/color_space.h>

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
    cv::Mat boxMat = boxFilter2D(image, 3, 3);
    timer.endClock("BoxFilter runtime");
    timer.startClock();
    cv::Mat gausMat = gaussianFilter2D(image, 5);
    timer.endClock("Gaussian Filter runtime");
    timer.startClock();
    cv::Mat medMat = medianFilter(image, 3, 3);
    timer.endClock("Gaussian Filter runtime");

    cv::Vec3b vec = cv::Vec3b(250, 0, 0);
    cv::Vec3d hsv_vec = rgb_pixel_to_hsv(vec);

    // Display the original and grayscale images
    cv::imshow("Original Image", image);
    cv::imshow("Box Filtered", boxMat);
    cv::imshow("Gaus Filtered", gausMat);
    cv::imshow("Med Filtered", medMat);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}