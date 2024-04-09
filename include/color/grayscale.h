#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <opencv2/opencv.hpp>

class GrayscaleTransformer {
public:
	void operator()(cv::Vec3b& pixel, const int* position) const noexcept;
};

cv::Mat grayscaleTransform(cv::Mat& input, bool in_place);


#endif GRAYSCALE_H