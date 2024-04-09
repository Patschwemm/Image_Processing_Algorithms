#include <opencv2/opencv.hpp>

cv::Mat vflip(cv::Mat& input, const bool inplace) {
	int img_rows = input.rows;
	int img_cols = input.cols;

	// If inplace is true, operate directly on the input matrix
	cv::Mat flipOut = inplace ? input : input.clone();
	// Pointer for bottom and top row
	cv::Vec3b* topRow = flipOut.ptr<cv::Vec3b>(0);
	cv::Vec3b* bottomRow = flipOut.ptr<cv::Vec3b>(img_rows - 1);

	for (int row = 0; row < img_rows / 2; ++row) {
		// Swap values
		std::swap_ranges(topRow, topRow + img_cols, bottomRow);
		// Move to the next row from the top
		topRow++;
		// Move to the previous row from the bottom
		bottomRow--;
	}

	return flipOut;
}

cv::Mat symmetricflip(cv::Mat& input, bool inplace) {
	int img_rows = input.rows;
	int img_cols = input.cols;

	// If inplace is true, operate directly on the input matrix
	cv::Mat flipOut = inplace ? input : input.clone();

	cv::Vec3b* pixPoint = input.ptr<cv::Vec3b>(0, 0);
	cv::Vec3b* flipPoint = flipOut.ptr<cv::Vec3b>(img_rows - 1, img_cols - 1);
	const cv::Vec3b* endPixel = pixPoint + input.cols * input.rows;

	int blue, green, red;
	for (; pixPoint != endPixel; pixPoint++) {
		blue = pixPoint[0][0];
		green = pixPoint[0][1];
		red = pixPoint[0][2];
		// assign current pixel values to flip pointer
		*flipPoint = cv::Vec3b(blue, green, red);
		// decrement for mirrored operation
		flipPoint--;
	}

	return flipOut;
}


cv::Mat hflip(cv::Mat& input, bool inplace) {
	int img_rows = input.rows;
	int img_cols = input.cols;

	std::cout << "Rows: " << img_rows << " Cols: " << img_cols << std::endl;
	return input;
}