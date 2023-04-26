cmake_minimum_required(VERSION 3.26)

project(krain)

add_executable(${PROJECT_NAME} main.cpp src/linear.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
