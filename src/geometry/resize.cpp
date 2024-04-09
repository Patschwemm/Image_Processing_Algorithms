#include <opencv2/opencv.hpp>
#include <cmath>

cv::Mat nearestInterpolation(const cv::Mat& input, const int height,const int width) {
	// Define the ratio of input
	double ratio_h = input.cols / static_cast<double>(height);
	double ratio_w = input.rows / static_cast<double>(width);
	// Initialize new resized matrix
	cv::Mat resizedMat(height, width, input.type());
	// Loop over new dimension and get nearest x and y coords
	int nearest_x, nearest_y;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			nearest_x = static_cast<int>(std::round(x * ratio_w));
			nearest_y = static_cast<int>(std::round(y * ratio_h));
			resizedMat.at<cv::Vec3b>(y, x) = input.at<cv::Vec3b>(nearest_y, nearest_x);
		}
	}
	return resizedMat;
}