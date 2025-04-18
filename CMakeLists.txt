cmake_minimum_required(VERSION 3.18.1)
project(Eendgine)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-03")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}lib/stb/stb_image.h")
    file(DOWNLOAD
        https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb/stb_image.h)
endif()

include_directories("lib")
add_subdirectory(lib/stb)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

add_library(Eendgine ${SOURCES})
target_link_libraries(Eendgine PRIVATE SDL2 assimp stb GLESv2 jsoncpp ${OpenMP_CXX_FLAGS})
target_compile_options(Eendgine PRIVATE -Werror ${OpenMP_CXX_FLAGS})
