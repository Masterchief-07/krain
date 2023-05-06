cmake_minimum_required(VERSION 3.26)

project(krain VERSION 0.0.1 LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/linear.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
