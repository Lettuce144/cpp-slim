cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cpp_slim)

# Add include directories
include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCES "source/*.cpp" "include/*.hpp")

# Add the main library target
add_library(cpp_slim STATIC ${SOURCES})

# Add test source files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Add the test executable target
add_executable(cpp_slim_tests ${TEST_SOURCES})

# Link the main library to the test executable
target_link_libraries(cpp_slim_tests cpp_slim)
