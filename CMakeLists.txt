cmake_minimum_required(VERSION 3.20)
project(ExampleProject)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

include_directories(vendor/Playground/PlaygroundLib/hdr)
add_subdirectory(vendor/Playground/PlaygroundLib)

add_executable(ExampleProject main.cpp)
target_link_libraries(ExampleProject PlaygroundLib)