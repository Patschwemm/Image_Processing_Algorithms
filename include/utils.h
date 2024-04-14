#ifndef UTILS_H
#define UTILS_H

#include <filesystem>
#include <string>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <iomanip>

std::string getCWD();
std::string type2str(int type);

cv::Mat readImgFromPath(const std::string path);
cv::Mat readLena(const std::string color);

// TODO: CLEAN UP THIS CODE, CURRETLY THROWS ERROR WITH LINK
class ExecutionTimer {
private:
    std::chrono::high_resolution_clock::time_point start, end;
public:
    void startClock() {
        start = std::chrono::high_resolution_clock::now();
        // unsync the I/O of C and C++.
        std::ios_base::sync_with_stdio(false);
    }

    void endClock(const std::string& operation_name) {
        end = std::chrono::high_resolution_clock::now();

        // Calculating total time taken by the program.
        double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;

        std::cout << "Time taken by " << operation_name << " is : "
            << std::fixed << std::setprecision(9) << time_taken;
        std::cout << " sec" << std::endl;
    }
};

int countNonMatchingPixels(const cv::Mat& mat1, const cv::Mat& mat2);


#endif UTILS_H