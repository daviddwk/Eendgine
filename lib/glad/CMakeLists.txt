cmake_minimum_required(VERSION 3.18.1)
project(glad)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "*.c" "*.h")
add_library(glad ${SOURCES})

