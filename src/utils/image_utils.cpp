#include "image_utils.h"

#include <string>
#include <vector>
#include <cstdint> // For std::uint8_t

ImageType getImageType(const std::string& filename){
    // find index of extension
    size_t dotIdx = filename.find_last_of(".");
    // if a match has been found for "." 
    if (dotIdx != std::string::npos) {
        std::string extension = filename.substr(dotIdx + 1);

        if (extension == "png") {
            return ImageType::PNG;
        } else if (extension == "jpg" || extension == "jpeg") {
            return ImageType::JPG;
        }

    }

    return ImageType::Unknown;
}

GrayscaleImage readGrayscaleImage(const std::string& filename) {
    ImageType imgType = getImageType(filename);

    
}



