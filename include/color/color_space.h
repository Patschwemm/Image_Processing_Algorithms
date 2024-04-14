#include <opencv2/opencv.hpp>


cv::Vec3d rgb_pixel_to_hsb(cv::Vec3d rgb_pixel) {
	cv::Vec3d normed_rgb_pixel = rgb_pixel / 255;
	double Cmin  = 0, double Cmax=1;
    int CminIdx, CmaxIdx;
    // Iterate over each channel
    for (int i = 0; i < 3; ++i) {
        if (normed_rgb_pixel[i] < Cmin ) {
            // Update minimum value if a smaller value is found and set idx
            Cmin  = normed_rgb_pixel[i];
            CminIdx = i;
        }
        if (normed_rgb_pixel[i] > Cmax) {
            // Update maximum value if a larger value is found and set idx
            Cmax = normed_rgb_pixel[i]; 
            CmaxIdx = i;
        }
    }
    double value = Cmax;
    double delta = Cmax - Cmin ;

    double hue;
    // Edge cases for Hue, keep in mind openCV uses BGR:
    if (CmaxIdx == 0) {
        // if blue is Cmax, 4.0 + (R-G) / (max-min)
        hue = 4.0 + (normed_rgb_pixel[2] - normed_rgb_pixel[1]) / (Cmax - Cmin);
    }
    else if (CmaxIdx == 1) {
        // if green is Cmax, 2.0 + (B-R) / (max-min)
        hue = 2.0 + (normed_rgb_pixel[0] - normed_rgb_pixel[2]) / (Cmax - Cmin);
    }
    else if (CmaxIdx == 2) {
        // if red is Cmax, 0.0 + (G-B)/(max-min)
        hue = 0.0 + (normed_rgb_pixel[1] - normed_rgb_pixel[0]) / (Cmax - Cmin);
    }

    double saturation;
    if (Cmax == 0) {
        saturation = 0.0;
    }
    else {
        saturation = delta / Cmax;
    }
    return cv::Vec3d(hue, saturation, value);
}