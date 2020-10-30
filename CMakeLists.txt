cmake_minimum_required(VERSION 3.0)
project(EGE3d C CXX)

string(ASCII 27 ESC)
message("-- ${ESC}[33mRunning EGE3d build system...${ESC}[m")

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/root")
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")

add_subdirectory(ege3d)
add_subdirectory(tests)

message("-- ${ESC}[33;1mDone!${ESC}[m")

