#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>
#include <string>
#include <cstdint> // For std::uint8_t

enum class ImageType{
    PNG,
    JPG,
    Unknown,
};

// Define a grayscale Image struct grayscale
struct GrayscaleImage {
    int width;
    int height;
    std::vector<std::uint8_t> data;
};
// Define an RGB Image struct 
struct RGBImage {
    int width;
    int height;
    std::vector<std::vector<uint8_t>> data;
};

// Get image type
ImageType getImageType(const std::string& filename);
// Read Image from a file
GrayscaleImage readGrayscaleImage(const std::string& filename);
RGBImage readRGBImage(const std::string& filename);

#endif // IMAGE_UTILS_H