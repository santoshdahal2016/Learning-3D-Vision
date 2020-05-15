cmake_minimum_required(VERSION 3.15)
project(Intrinsic_Calculation)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED)

include_directories("/usr/include/eigen3" )


FIND_PACKAGE(OpenCV REQUIRED)


add_executable(intrinsicCalculation1 intrinsicCalculation1.cpp)
TARGET_LINK_LIBRARIES (intrinsicCalculation1  ${OpenCV_LIBS} )