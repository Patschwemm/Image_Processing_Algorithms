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

class GrayscaleTransformerFloat {
public:
    void operator()(cv::Vec3d& pixel, const int* position) const noexcept {
        double avg = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
        pixel[0] = avg;
        pixel[1] = avg;
        pixel[2] = avg;
    }
};

cv::Mat channelShrink(cv::Mat input) {
    int rows = input.rows;
    int columns = input.cols;

    cv::Mat grayMat = cv::Mat::zeros(rows, columns, CV_64F);

    input.forEach<cv::Vec3d>([&grayMat](cv::Vec3d& pixel, const int* pos) {
        // Process pixel from input matrix to grayMat
        double sum = pixel[0] + pixel[1] + pixel[2];
        grayMat.at<double>(pos[0], pos[1]) = sum/3.0;
        });

    return grayMat;
}

cv::Mat grayscaleTransform(cv::Mat& input, bool in_place, bool keepdim) {
    if (in_place) {
        // Inplace Grayscale transform - all 3 channels have same value
        input.forEach<cv::Vec3b>(GrayscaleTransformer());
        return input; // Return modified input
    } else {
        // cloning the original channel 
        cv::Mat clone = input.clone();
        // If one channel is wanted replace the clone channel
        if (!keepdim) {
            clone.forEach<cv::Vec3d>(GrayscaleTransformerFloat());
            return channelShrink(clone);
        }
        else {
            clone.forEach<cv::Vec3b>(GrayscaleTransformer());
            return clone; // Return a new Mat with transformed pixels
        }
    }
}

