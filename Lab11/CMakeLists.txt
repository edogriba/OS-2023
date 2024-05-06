cmake_minimum_required(VERSION 3.0)
project(PageTableSimulator)

set(CMAKE_CXX_STANDARD 17)

# Find Boost
find_package(Boost REQUIRED COMPONENTS program_options)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Set the include directory path
include_directories(include)

# Set the source files
set(SOURCES
    src/main.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set compiler flags to suppress warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link against Boost libraries
target_link_libraries(${PROJECT_NAME} Boost::program_options)
