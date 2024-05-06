cmake_minimum_required(VERSION 3.12)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include(FetchContent)

# Fetch the nlohmann/json library
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
set(JSON_BuildTests OFF CACHE BOOL "Build the unit tests for nlohmann/json" FORCE)
FetchContent_MakeAvailable(json)

# Set the source files for your project
set(SOURCES
    src/main.cpp
    src/AddressTranslator.cpp
    src/ConfigParser.cpp
    src/Segment.cpp
    src/Memory.cpp
)

set(HEADERS
    include/cse4733/AddressTranslator.hpp
    include/cse4733/ConfigParser.hpp
    include/cse4733/Segment.hpp
    include/cse4733/Memory.hpp
    )

# Set the include directories for your project
set(INCLUDE_DIRS
    include
)

# Create the executable for your project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link the nlohmann/json library
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Set the include directories for your project
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
