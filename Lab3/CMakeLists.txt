cmake_minimum_required(VERSION 3.0)
project(SchedulingExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Header files
set(HEADERS
    include/cse4733/process.hpp
    include/cse4733/first_come_first_served.hpp
    include/cse4733/round_robin.hpp
    include/cse4733/shortest_job_first.hpp)

set(SOURCES src/process.cpp
        src/first_come_first_served.cpp
        src/round_robin.cpp
        src/shortest_job_first.cpp)

# Create a shared library target
add_library(cpulib SHARED ${SOURCES} ${HEADERS})

# Add the executable target
add_executable(cpuexe src/main.cpp)

# Include the 'include' directory
target_include_directories(cpulib PRIVATE include/cse4733)

# Link the executable with the shared library
target_link_libraries(cpuexe PRIVATE cpulib)

# Include the 'include' directory
target_include_directories(cpuexe PRIVATE include/cse4733)

# Include the 'tests' directory
#add_subdirectory(tests)
