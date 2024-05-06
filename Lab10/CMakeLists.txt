cmake_minimum_required(VERSION 3.10)

# set the project name
project(TLB_MMU_Simulation)

set(CMAKE_CXX_STANDARD 17)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Set the include directory path
include_directories(include)

set(SOURCES src/main.cpp
   src/MMU.cpp
   src/TLB.cpp)

set(HEADERS include/cse4733/MMU.hpp
  include/cse4733/TLB.hpp)

# add the executable
add_executable(TLB_MMU_Simulation ${SOURCES} ${HEADERS})

