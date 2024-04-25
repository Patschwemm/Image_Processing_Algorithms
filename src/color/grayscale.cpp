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

cv::Mat channelShrink(cv::Mat input) {
    int rows = input.rows;
    int columns = input.cols;

    cv::Mat_<int> onechmat(rows, columns);

    input.forEach<cv::Vec3b>([&onechmat](cv::Vec3b& pixel, const int* pos) {
        // Process pixel from input matrix and push to onechmat
        // For demonstration, let's just push the sum of pixel values to onechmat
        int sum = pixel[0] + pixel[1] + pixel[2];
        onechmat(pos[0], pos[1]) = sum;
        });

    return onechmat;
}

cv::Mat grayscaleTransform(cv::Mat& input, bool in_place, bool keepdim) {
    if (in_place) {
        input.forEach<cv::Vec3b>(GrayscaleTransformer());
        return input; // Return modified input
    } else {
        cv::Mat clone = input.clone();
        clone.forEach<cv::Vec3b>(GrayscaleTransformer());

        if (!keepdim) {
            return channelShrink(clone);
        }
        else {
        return clone; // Return a new Mat with transformed pixels
        }
    }
}

