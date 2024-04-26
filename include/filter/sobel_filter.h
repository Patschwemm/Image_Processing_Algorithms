#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H


std::array<cv::Mat, 2> sobelFilter2DRaw(cv::Mat& input);
cv::Mat sobelFilter2D(cv::Mat& input, bool toGray);
cv::Mat gradImgMagnitude(cv::Mat& input, bool toGray);
cv::Mat gradImgOrientation(cv::Mat& input);

#endif SOBEL_FILTER_H