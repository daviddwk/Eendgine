cmake_minimum_required(VERSION 3.18.1)
project(stb)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES stb_image.cpp stb_image.h)
add_library(stb ${SOURCES})

