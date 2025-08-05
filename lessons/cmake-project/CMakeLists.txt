cmake_minimum_required(VERSION 4.0)

project(CMakeProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.h.in config.h)

add_executable(CMakeProject main.cpp)

target_include_directories(CMakeProject PUBLIC "${PROJECT_BINARY_DIR}")
