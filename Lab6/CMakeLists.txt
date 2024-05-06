cmake_minimum_required(VERSION 3.12)
project(memory_simulation)

set(CMAKE_CXX_STANDARD 14)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

add_executable(os_signals src/main.cpp)

