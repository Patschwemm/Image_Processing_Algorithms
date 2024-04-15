#include <opencv2/opencv.hpp>

cv::Vec3d rgb_pixel_to_hsv(cv::Vec3b rgb_pixel) {
    cv::Vec3d normed_rgb_pixel = static_cast<cv::Vec3d>(rgb_pixel) / 255;
    double Cmin = 1;
    double Cmax = 0;
    int CminIdx;
    int CmaxIdx;
    // Iterate over each channel
    for (int i = 0; i < 3; ++i) {
        if (normed_rgb_pixel[i] < Cmin) {
            // Update minimum value if a smaller value is found and set idx
            Cmin = normed_rgb_pixel[i];
            CminIdx = i;
        }
        if (normed_rgb_pixel[i] > Cmax) {
            // Update maximum value if a larger value is found and set idx
            Cmax = normed_rgb_pixel[i];
            CmaxIdx = i;
        }
    }
    double value = Cmax;
    double delta = Cmax - Cmin;
    double hue;
    // Edge cases for Hue, keep in mind openCV uses BGR:
    if (delta == 0) {
        hue = 0.0;
    }
    else if (CmaxIdx == 0) {
        // If red is Cmax
        hue = 60.0 * fmod(((normed_rgb_pixel[1] - normed_rgb_pixel[0]) / delta), 6.0);
    }
    else if (CmaxIdx == 1) {
        // If green is Cmax
        hue = 60.0 * (((normed_rgb_pixel[0] - normed_rgb_pixel[2]) / delta) + 2.0);
    }
    else if (CmaxIdx == 2) {
        hue = 60.0 * (((normed_rgb_pixel[2] - normed_rgb_pixel[1]) / delta) + 4.0);
    }
    hue = std::abs(hue);
    // Set Saturation
    double saturation;
    if (Cmax == 0) {
        saturation = 0.0;
    }
    else {
        saturation = delta / Cmax;
    }

    return cv::Vec3d(hue, saturation, value);
}