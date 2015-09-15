

cmake_minimum_required(VERSION 2.6)

project(map_editor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${map_editor_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${map_editor_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-W -I -Wall -Wextra -pedantic -std=c++0x")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_subdirectory(src)
