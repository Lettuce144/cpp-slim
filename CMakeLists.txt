cmake_minimum_required(VERSION 3.10)

# Set the project name and C++ standard
project(cpp_slim VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include/slim)

# Compiler flags for warnings, conversion, and coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcx16 -Wall -Wsuggest-override -Wconversion -g --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Directories for generated binaries, objects, and test outputs
set(BIN_DIR "${CMAKE_BINARY_DIR}/bin")
set(OBJ_DIR "${CMAKE_BINARY_DIR}/obj/lib")
set(TEST_OBJ_DIR "${CMAKE_BINARY_DIR}/obj/tests")

# Source and test file discovery
file(GLOB_RECURSE SOURCES "source/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Main library target
add_library(cpp_slim STATIC ${SOURCES})
target_include_directories(cpp_slim PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Test executable target
add_executable(cpp_slim_tests ${TEST_SOURCES})
target_link_libraries(cpp_slim_tests PRIVATE cpp_slim)

add_subdirectory(examples/custom-type)

# Specify output directories for library and executables
set_target_properties(cpp_slim PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
)
set_target_properties(cpp_slim_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

# Coverage report generation with lcov and genhtml
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E remove -f coverage/all.info coverage/coverage.info
    COMMAND ${CMAKE_COMMAND} -E remove -f ${OBJ_DIR}/*.gcda
    COMMAND ${BIN_DIR}/cpp_slim_tests
    COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR}/obj --base-directory . --output-file coverage/all.info -q
    COMMAND lcov --extract coverage/all.info ${CMAKE_SOURCE_DIR}/include/\* ${CMAKE_SOURCE_DIR}/source/\* --output-file coverage/coverage.info -q
    COMMAND genhtml coverage/coverage.info --output-directory coverage/
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Clean coverage output
add_custom_target(clean_coverage
    COMMAND ${CMAKE_COMMAND} -E remove -rf coverage
)

# Add tests for CTest (if needed for further testing with ctest)
enable_testing()
add_test(NAME cpp_slim_tests COMMAND cpp_slim_tests)
