#ifndef RESIZE_H
#define RESIZE_H

cv::Mat nearestInterpolation(const cv::Mat& input, const int height, const int width);
cv::Mat bilinearInterpolation(const cv::Mat& input, const int height, const int width);

#endif RESIZE_H
