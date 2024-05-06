cmake_minimum_required(VERSION 3.12)
project(memory_simulation)

set(CMAKE_CXX_STANDARD 14)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")

# Source files
set(SOURCES src/main.cpp
    src/MemoryAllocator.cpp
    src/Process.cpp)

# Header files
set(HEADERS src/MemoryAllocator.h
    src/Process.h)

add_executable(memory_simulation ${SOURCES} ${HEADERS})

