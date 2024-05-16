cmake_minimum_required(VERSION 3.18.1)
project(eendgine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")
add_library(eendgine ${SOURCES})

