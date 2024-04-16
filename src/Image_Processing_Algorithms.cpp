// Image_Processing_Algorithms.cpp : Defines the entry point for the application.

#include "Image_Processing_Algorithms.h"
#include <opencv2/opencv.hpp>
#include <utils.h>
#include <color/grayscale.h>
#include <geometry/flip.h>
#include <geometry/resize.h>
#include <filter/filter_alg.h>
#include <filter/noise_induction.h>
#include <color/color_space.h>

int main() {

    cv::Mat image = readLena("rgb");

    // to track time
    ExecutionTimer timer = ExecutionTimer();

    timer.startClock();
    cv::Mat spMat = noiseImgSaltPepper(image, 0.1, false);
    timer.endClock("SP Noise runtime");
    timer.startClock();
    cv::Mat medMat = medianFilter(spMat, 3, 3);
    timer.endClock("Med Filter runtime");

    cv::Vec3b vec = cv::Vec3b(250, 0, 0);
    cv::Vec3d hsv_vec = rgb_pixel_to_hsv(vec);

    // Display the original and grayscale images
    //cv::imshow("Original Image", image);
    cv::imshow("SP noisy", spMat);
    cv::imshow("Med Filtered", medMat);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}