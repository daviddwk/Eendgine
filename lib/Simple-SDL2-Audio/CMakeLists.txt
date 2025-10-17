cmake_minimum_required(VERSION 3.18.1)
project(Simple-SDL2-Audio)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES audio.c audio.h)
add_library(Simple-SDL2-Audio ${SOURCES})

