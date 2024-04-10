#include <opencv2/opencv.hpp>
#include <cmath>
#include <algorithm>

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

cv::Mat bilinearInterpolation(const cv::Mat& input, const int height, const int width) {
	// Define the ratio of input
	double ratio_h = input.cols / static_cast<double>(height);
	double ratio_w = input.rows / static_cast<double>(width);
	// Initialize new resized matrix
	cv::Mat resizedMat(height, width, input.type());
	// Loop over new dimension and get nearest x and y coords
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// get exact pixel
			float x_new = x * ratio_w;
			float y_new = y * ratio_h;
			// get right, bottom neighborhood pixel
			int right_x = std::min(input.cols - 1, static_cast<int>(ceil(x_new)));
			int bot_y = std::min(input.rows - 1, static_cast<int>(ceil(y_new)));
			// get left, top neighborhood pixel
			int left_x = std::max(0, static_cast<int>(floor(x_new)));
			int top_y = std::max(0, static_cast<int>(floor(y_new)));
			// define weight based on distance to original pixel
			float dx = x_new - left_x;
			float dy = y_new - top_y;
			// weigh vectors accordingly
			cv::Vec3f weighted_avg = (1 - dx) * (1 - dy) * input.at<cv::Vec3b>(top_y, left_x) +
				(1 - dx) *  dy * input.at<cv::Vec3b>(bot_y, left_x) +
				dx * (1 - dy) * input.at<cv::Vec3b>(top_y, right_x) +
				dx * dy * input.at<cv::Vec3b>(bot_y, right_x);
			resizedMat.at<cv::Vec3b>(y, x) = weighted_avg;
		}
	}
	return resizedMat;
}