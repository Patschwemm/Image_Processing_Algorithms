#ifndef FLIP_H
#define FLIP_H

cv::Mat symmetricflip(cv::Mat& input, bool inplace);
cv::Mat vflip(cv::Mat& input, bool inplace);
cv::Mat hflip(cv::Mat& input, bool inplace);

#endif FLIP_H
