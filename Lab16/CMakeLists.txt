cmake_minimum_required(VERSION 3.10)
project(PowerCalculator)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(include)

set(SOURCES src/power_calculator.cpp
	src/main.cpp)
	
set(HEADERS include/cse4733/power_calculator.hpp)

# Set the include directories for your project
set(INCLUDE_DIRS
    include
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Set the include directories for your project
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
