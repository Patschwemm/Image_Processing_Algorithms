#include <opencv2/opencv.hpp>
#include <filter/filter_alg.h>
#include <filter/sobel_filter.h>

cv::Mat cannyEdgeDetection(cv::Mat& input) {
	// 1. Apply Gaussian Filter
	cv::Mat gausMat = gaussianFilter2D(input, 3);
	// 2. Find intensity gradients and gradient orientation of the image
	cv::Mat gradImg = gradImgMagnitude(input, true);
	cv::Mat orientImg = gradImgOrientation(input);
	// 3. Non-maximum supression: thin wide "rides" to single pixel width


	return gausMat;
}

cv::Mat nonmaximumSupression(cv::Mat& input) {
	// given an image of intesity gradients

	cv::Mat nmsMat;
	return nmsMat;
}