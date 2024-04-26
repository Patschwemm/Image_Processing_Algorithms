#include <opencv2/opencv.hpp>
#include <color/grayscale.h>
#include <filter/filter_kernel.h>
#include <filter/filter_alg.h>

std::array<cv::Mat, 2> sobelFilter2DRaw(cv::Mat& input) {
	// Init sobel filters
	cv::Mat sobelKernelX = createSobelFilter("x");
	cv::Mat sobelKernelY = createSobelFilter("y");
	// Make a copy of the input matrix
	cv::Mat inputCopy = input.clone();
	// Filter the copied input matrix with sobel kernels
	cv::Mat sobelMatX = filterAlg(input, sobelKernelX);
	cv::Mat sobelMatY = filterAlg(input, sobelKernelY);
	return { sobelMatX, sobelMatY };
}

cv::Mat sobelFilter2D(cv::Mat& input, bool toGray) {
	// Get SobelOutput
	auto sobelOuts = sobelFilter2DRaw(input);
	// Combine X and Y sobelResults
	cv::Mat sobelMat = sobelOuts[0] + sobelOuts[1];
	// Combine the results of X and Y sobel filters
	cv::normalize(sobelMat, sobelMat, 0, 1, cv::NORM_MINMAX);

	if (toGray) {
		sobelMat = grayscaleTransform(sobelMat, false, false);
	}
	return sobelMat;
}

cv::Mat gradImgMagnitude(cv::Mat& input, bool toGray) {

	// Get SobelOutput
	auto sobelOuts = sobelFilter2DRaw(input);
	// get X and Y sobelmats
	cv::Mat sobelMatX = sobelOuts[0];
	cv::Mat sobelMatY = sobelOuts[1];

	cv::Mat gradImg;
	cv::sqrt(sobelMatX.mul(sobelMatX) + sobelMatY.mul(sobelMatY), gradImg);
	if (toGray) {
		gradImg = grayscaleTransform(gradImg, false, false);
	}
	cv::normalize(gradImg, gradImg, 0, 1, cv::NORM_MINMAX);
	return gradImg;
}

cv::Mat gradImgOrientation(cv::Mat& input) {
	// Get SobelOutput
	auto sobelOuts = sobelFilter2DRaw(input);
	// get X and Y sobelmats
	cv::Mat sobelMatX = sobelOuts[0];
	cv::Mat sobelMatY = sobelOuts[1];
	// Combine the results of X and Y sobel filters
	cv::Mat orientImg = cv::Mat::zeros(sobelMatX.rows, sobelMatX.cols, CV_64F);

	orientImg.forEach<double>([&sobelMatX, &sobelMatY](double& pixel, const int* pos) {
		// Get respective vector from sobelMatrices
		cv::Vec3d sobelXVec = sobelMatX.at<cv::Vec3d>(pos[0], pos[1]);
		cv::Vec3d sobelYVec = sobelMatY.at<cv::Vec3d>(pos[0], pos[1]);
		// Convert both to grayscale
		double xSum = sobelXVec[0] + sobelXVec[1] + sobelXVec[2];
		double ySum = sobelYVec[0] + sobelYVec[1] + sobelYVec[2];
		// Get atan2 value for orientation
		pixel = std::atan2(xSum, ySum);
		});

	cv::normalize(orientImg, orientImg, 0, 1, cv::NORM_MINMAX);
	return orientImg;
}