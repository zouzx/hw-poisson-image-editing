cmake_minimum_required(VERSION 3.0.0)
project(poisson_image_editing VERSION 0.1.0)

find_package(OpenCV REQUIRED)

add_executable(get_mask src/get_mask.cpp)
target_link_libraries(get_mask "${OpenCV_LIBS}")


