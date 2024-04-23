#include <opencv2/opencv.hpp>
#include <filter/filter_alg.h>

cv::Mat cannyEdgeDetection(cv::Mat& input) {
	// 1. Apply Gaussian Filter
	cv::Mat gausMat = gaussianFilter2D(input, 3);
	// 2. Find intensity gradients of the image


	return gausMat;
}