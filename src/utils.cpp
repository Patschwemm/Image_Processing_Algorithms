#include <filesystem>
#include <string>
#include <opencv2/opencv.hpp>


std::string getCWD() {
	std::filesystem::path parent_path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	
	return parent_path.string();
}

std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
    }

    r += "C";
    r += (chans + '0');

    return r;
}

cv::Mat readImgFromPath(const std::string path) {
    // Load an image
    std::string im_path = getCWD() + path;
    cv::Mat image = cv::imread(im_path);

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return image;
    }

    return image;
}

cv::Mat readLena(const std::string color) {
    // Load an image
    if (color == "rgb") {
        return readImgFromPath("\\images\\lena_rgb.png");
    }
    else if (color == "gray") {
        return readImgFromPath("\\images\\lena_gray.png");
    }
    else {
        std::cerr << "Error: Could not open or find the Lena color input!" << std::endl;
        cv::Mat emptyMat;
        return emptyMat;
    }
    
}