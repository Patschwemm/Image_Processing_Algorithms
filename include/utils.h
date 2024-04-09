#ifndef UTILS_H
#define UTILS_H

#include<string>

std::string getCWD();
std::string type2str(int type);

cv::Mat readImgFromPath(const std::string path);
cv::Mat readLena(const std::string color);

#endif UTILS_H