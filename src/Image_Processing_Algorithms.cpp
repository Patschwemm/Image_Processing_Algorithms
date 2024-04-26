// Image_Processing_Algorithms.cpp : Defines the entry point for the application.

#include "Image_Processing_Algorithms.h"
#include <opencv2/opencv.hpp>
#include <utils.h>
#include <color/grayscale.h>
#include <geometry/flip.h>
#include <geometry/resize.h>
#include <filter/filter_alg.h>
#include <filter/noise_induction.h>
#include <filter/sobel_filter.h>
#include <color/color_space.h>

int main() {

    cv::Mat image = readLena("rgb");

    // to track time
    ExecutionTimer timer = ExecutionTimer();

    timer.startClock();
    cv::Mat spMat = noiseImgSaltPepper(image, 0.1, false);
    timer.endClock("SP Noise runtime");
    timer.startClock();
    cv::Mat sobelMat = sobelFilter2D(image, true);
    timer.endClock("Sobel Filter runtime");
    timer.startClock();
    cv::Mat gradMat = gradImgMagnitude(image, true);
    timer.endClock("Mag Filter runtime");
    timer.startClock();
    cv::Mat orientMat = gradImgOrientation(image);
    timer.endClock("Sobel Filter runtime");

    // Display the original and grayscale images
    cv::imshow("SP noisy", spMat);
    cv::imshow("Sobel Filtered", sobelMat);
    cv::imshow("Mag Filtered", gradMat);
    cv::imshow("Orient Filtered", orientMat);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}