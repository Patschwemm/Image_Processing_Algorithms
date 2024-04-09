cmake_minimum_required(VERSION 3.8)

project("Image_Processing_Algorithms")

# Set the directory where your source files are located
set(SOURCES
    src/Image_Processing_Algorithms.cpp
    src/utils.cpp
    src/color/grayscale.cpp
    src/geometry/flip.cpp
    src/geometry/resize.cpp
)

# Set the directory where your header files are located
set(INCLUDES
    include/Image_Processing_Algorithms.h
    include/utils.h
    include/color/grayscale.h
    include/geometry/flip.h
    include/geometry/resize.h
)

# Set the directory where your include files are located
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find OpenCV package
set(OpenCV_DIR "D:/VisualStudio/Downloads/opencv/build")
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(Image_Processing_Algorithms ${SOURCES} ${INCLUDES})

# Link against OpenCV libraries
target_link_libraries(Image_Processing_Algorithms ${OpenCV_LIBS})

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Image_Processing_Algorithms PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.