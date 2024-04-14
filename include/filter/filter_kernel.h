#ifndef FILTER_KERNEL_H
#define FILTER_KERNEL_H

cv::Mat createBoxFilter(int height, int width);
cv::Mat createGaussianFilter(int k_size);

#endif FILTER_KERNEL_H