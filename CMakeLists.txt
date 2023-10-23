cmake_minimum_required(VERSION 3.18.1)
project(quack)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("lib")

add_subdirectory(lib/glad)
add_subdirectory(lib/stb)
add_subdirectory(lib/eendgine)


file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(quack ${SOURCES})
target_link_libraries(quack eendgine SDL2 assimp stb glad)
