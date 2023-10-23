cmake_minimum_required(VERSION 3.18.1)
project(game)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT EXISTS "${CMAKE_SOURCE_DIR}lib/stb/stb_image.h")
    file(DOWNLOAD
        https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
        ${CMAKE_SOURCE_DIR}/lib/stb/stb_image.h)
endif()
include_directories("lib")

add_subdirectory(lib/glad)
add_subdirectory(lib/stb)
add_subdirectory(lib/eendgine)


file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(game ${SOURCES})
set_target_properties(
    game 
    PROPERTIES 
        OUTPUT_NAME "game"
        SUFFIX ".out"
)
target_link_libraries(game eendgine SDL2 assimp stb glad)
