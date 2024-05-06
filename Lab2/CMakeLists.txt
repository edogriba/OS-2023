cmake_minimum_required(VERSION 3.0)
project(ProcessExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Include the 'include' directory
include_directories(include/cse4733)

# Create a shared library target
add_library(processlib SHARED src/process.cpp)

# Add the executable target
add_executable(processexe src/main.cpp)

# Link the executable with the shared library
target_link_libraries(processexe PRIVATE processlib)

# Include the 'tests' directory
#add_subdirectory(tests)