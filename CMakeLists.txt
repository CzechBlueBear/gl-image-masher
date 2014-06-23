cmake_minimum_required(VERSION 2.8)
project(tiffcruncher C CXX)

find_package(OpenGL REQUIRED)
find_package(TIFF REQUIRED)
find_package(PNG REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_definitions(-std=c++11 -O -Wall -Wextra)

# if you want funky colors in error messages (requires gcc-4.9 or higher)
#add_definitions(-fdiagnostics-color=auto)

add_subdirectory(src build)

include_directories(${OPENGL_INCLUDE_PATH} ${GLEW_INCLUDE_PATH} ${GLFW_INCLUDE_DIRS} ${TIFF_INCLUDE_PATH} ${PNG_INCLUDE_PATH} src)
