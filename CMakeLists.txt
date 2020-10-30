cmake_minimum_required(VERSION 3.0)
project(EGE3d C CXX)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/root")
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")

add_subdirectory(src)

