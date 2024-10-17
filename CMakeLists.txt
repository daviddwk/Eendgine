cmake_minimum_required(VERSION 3.18.1)
project(Eendgine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")
add_library(Eendgine ${SOURCES})


target_compile_options(Eendgine PRIVATE -Wall -lglfw -lGL  ${OpenMP_CXX_FLAGS})
target_link_libraries(Eendgine PRIVATE -lglfw -lGL  ${OpenMP_CXX_FLAGS})
