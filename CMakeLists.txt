project(StrelnikovArgus CXX)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(ImageMagick)
find_package(ImageMagick COMPONENTS Magick++)
#find_package(ImageMagick COMPONENTS convert)
#find_package(ImageMagick COMPONENTS Magick++ convert)
include_directories(${ImageMagick_INCLUDE_DIRS})

add_executable(image_processor main.cpp)
target_link_libraries(image_processor ${ImageMagick_LIBRARIES})