cmake_minimum_required(VERSION 3.15)

project(neural-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(neurons  src/neurons.cpp src/trainer.cpp)

add_executable(neural-test src/driver.cpp)

target_link_libraries(neural-test neurons)
