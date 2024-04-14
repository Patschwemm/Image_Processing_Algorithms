#include <opencv2/opencv.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

cv::Mat createBoxFilter(int height, int width) {
	// Create a matrix filled with ones
	cv::Mat kernel = cv::Mat::ones(height, width, CV_64F);

	// Normalize the kernel
	kernel /= (double)(height * width);

	return kernel;
}

double gaussianValue(int x, double sigma) {
	// function for 1D gaussian value
	double val = (1 / (std::sqrt(2 * M_PI) * sigma) * exp(-(x * x) / (2 * sigma * sigma)));
	return val;
}

cv::Mat createGaussianFilter(int k_size) {
	// set sigma according to kernel size
	double sigma = (static_cast<double>(k_size) - 1) / (2 * 3);
	cv::Mat kernel = cv::Mat::ones(k_size, k_size, CV_64F);
	int center = (k_size - 1) / 2;
	// loop over kernel and set values -> symmetric mat
	for (int i = 0; i < k_size; ++i) {
		for (int j = i; j < k_size; ++j) {
			double x = i - center;
			double y = j - center;
			double gaus_val = gaussianValue(x, sigma) * gaussianValue(y, sigma);

			kernel.at<double>(i, j) = gaus_val;
			kernel.at<double>(j, i) = gaus_val;
		}
	}
	// normalize kernel:
	kernel = kernel / cv::sum(kernel)[0];

	return kernel;
}