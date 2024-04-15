#ifndef FILTER_ALG_H
#define FILTER_ALG_H

cv::Mat filterAlg(cv::Mat& input, cv::Mat& kernel);
cv::Mat boxFilter2D(cv::Mat& input, int height, int width);
cv::Mat gaussianFilter2D(cv::Mat& input, int k_size);
bool compareVec3b(const cv::Vec3b& a, const cv::Vec3b& b);
cv::Mat medianFilter(cv::Mat& input, const int height, const int width);

#endif FILTER_ALG_H