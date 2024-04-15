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

// Custom comparison function for sorting Vec3b elements by channel values
bool compareVec3b(const cv::Vec3b& a, const cv::Vec3b& b) {
	// Sort by channel values in ascending order
	return (a[0] < b[0]) || (a[0] == b[0] && a[1] < b[1]) || (a[0] == b[0] && a[1] == b[1] && a[2] < b[2]);
}

cv::Mat medianFilter(cv::Mat& input, const int height, const int width) {
	int k_height = (height - 1) / 2;
	int k_width = (width - 1) / 2;
	// Create copy of input for the result filtered Mat
	cv::Mat filteredMat = input.clone();
	// Loop over image pixels
	for (int y = 0; y < input.rows; ++y) {
		for (int x = 0; x < input.cols; ++x) {

			std::vector<cv::Vec3b> med_arr;
			// Loop over kernel
			for (int i = -k_height; i <= k_height; ++i) {
				// Edge case if outside vertical border:
				if (((y + i) < 0) || ((y + i) > input.rows)) {
					continue;
				}
				for (int j = -k_width; j <= k_width; ++j) {
					// Edge case if outside horizontal border:
					if (((x + j) < 0) || ((x + j) > input.cols)) {
						continue;
					}
					med_arr.push_back(input.at<cv::Vec3b>(y + i, x + j));
				}
			}
		// Sort the pixel values independently for each channel
		std::sort(med_arr.begin(), med_arr.end(), compareVec3b);
		// Replace the central pixel value with the median value
		filteredMat.at<cv::Vec3b>(y, x) = med_arr[med_arr.size() / 2];
		}
	}
	return filteredMat;
}