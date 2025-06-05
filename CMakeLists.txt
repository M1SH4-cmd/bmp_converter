cmake_minimum_required(VERSION 3.30)
project(bmp_converter)

set(CMAKE_CXX_STANDARD 17)

add_executable(bmp_converter main.cpp
        bmp_processor.cpp
        bmp_processor.h)
