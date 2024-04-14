#include <opencv2/opencv.hpp>
#include <filter/filter_kernel.h>
#include <utils.h>

cv::Mat filterAlg(cv::Mat& input, cv::Mat& kernel) {
	int k_height = (kernel.rows - 1) / 2;
	int k_width = (kernel.cols - 1) / 2;
	// Create copy of input for the result filtered Mat
	cv::Mat filteredMat = input.clone();
	// Loop over image pixels
	for (int y = 0; y < input.rows; ++y) {
		for (int x = 0; x < input.cols; ++x) {
			// Loop over kernel
			cv::Vec3b sum(0, 0, 0);
			for (int i = -k_height; i <= k_height; ++i) {
				// Edge case if outside vertical border:
				if (((y + i) < 0) || ((y + i) > input.rows)) {
					continue;
				}
				for (int j = -k_width; j <= k_width; ++j) {
					// Edge case if outside horizontal border:
					if (((x + j) < 0) || ((x + j)>input.cols)) {
						continue;
					}
					sum += input.at<cv::Vec3b>(y + i, x + j) * kernel.at<double>(i + k_height, j + k_width);
				}
			}
			// Set pixel of new Mat to new filter sum 
			filteredMat.at<cv::Vec3b>(y, x) = sum;
		}
	}
	return filteredMat;
}

cv::Mat boxFilter2D(cv::Mat& input, int height, int width) {
	// Init. box filter
	cv::Mat boxKernel = createBoxFilter(height, width);
	// Run Filter
	cv::Mat boxFilteredMat = filterAlg(input, boxKernel);
	return boxFilteredMat;
}

cv::Mat gaussianFilter2D(cv::Mat& input, int k_size) {
	// Init. gaussian filter
	cv::Mat gausKernel = createGaussianFilter(k_size);
	// Run Filter
	cv::Mat boxFilteredMat = filterAlg(input, gausKernel);
	return boxFilteredMat;
}