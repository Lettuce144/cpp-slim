cmake_minimum_required(VERSION 3.12)
project(custom_type)

# Add your source files here
set(SOURCES
    Main.cpp
    Vector2.hpp
)


# Add any additional libraries here
set(LIBRARIES
    cpp_slim
)

add_executable(custom_type ${SOURCES})
target_link_libraries(custom_type ${LIBRARIES})