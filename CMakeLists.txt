cmake_minimum_required(VERSION 3.26)

project(krain VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
	)
FetchContent_MakeAvailable(matplotlib)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2 
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
  Matrix
  GIT_REPOSITORY https://github.com/Masterchief-07/MATRIX.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(Matrix)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/MATRIX)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${matplotlib_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${Matrix_SOURCE_DIR}/matrix)
target_link_libraries(${PROJECT_NAME} matplotlib_cpp Matrix)

#----------------testing---------------------------------------------------------------
add_executable(tests tests/tests.cpp)
target_include_directories(tests PRIVATE include ${matrix_SOURCE_DIR}/matrix)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Matrix)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)