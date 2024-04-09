// Image_Processing_Algorithms.cpp : Defines the entry point for the application.

#include "Image_Processing_Algorithms.h"
#include <opencv2/opencv.hpp>
#include <utils.h>
#include <color/grayscale.h>
#include <geometry/flip.h>

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
    cv::Mat grayscaleImg = grayscaleTransform(image, false);
    timer.endClock("grayscale");
    timer.startClock();
    cv::Mat symmetricflipImg = symmetricflip(image, false);
    timer.endClock("Symmteric");
    cv::Mat vflipImg = vflip(image, false);
    timer.endClock("vflip");
    timer.startClock();
    cv::Mat hflipImg = hflip(image, false);
    timer.endClock("hflip");

    // Display the original and grayscale images
    cv::imshow("Original Image", image);
    //cv::imshow("Grayscale Image", grayscaleImg);
    cv::imshow("Symmetric Flipped Image", symmetricflipImg);
    cv::imshow("Vertical Flipped Image", vflipImg);
    cv::imshow("Horizontal Flipped Image", hflipImg);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}