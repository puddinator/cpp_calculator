cmake_minimum_required(VERSION 3.28)
project(cpp_calculator)

set(CMAKE_CXX_STANDARD 20)

set(Headers Calculator.h)

add_executable(cpp_calculator ${PROJECT_SOURCE_DIR}/ main.cpp Calculator.cpp)
