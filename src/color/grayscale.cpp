#include <opencv2/opencv.hpp>

class GrayscaleTransformer {
public:
	void operator()(cv::Vec3b& pixel, const int* position) const noexcept {
		int avg = (pixel[0] + pixel[1] + pixel[2]) / 3;
		pixel[0] = avg;
		pixel[1] = avg;
		pixel[2] = avg;
	}
};


cv::Mat grayscaleTransform(cv::Mat& input, bool in_place) {
    if (in_place) {
        input.forEach<cv::Vec3b>(GrayscaleTransformer());
        return input; // Return modified input
    } else {
        cv::Mat clone = input.clone();
        clone.forEach<cv::Vec3b>(GrayscaleTransformer());
        return clone; // Return a new Mat with transformed pixels
    }
}