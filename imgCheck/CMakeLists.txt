cmake_minimum_required(VERSION 3.10)

project(imgCheck)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Add subdirectories
add_subdirectory(src)

# Main executable
add_executable(imgCheck main.cpp)

# Link the main executable with the library from src
target_link_libraries(imgCheck my_image)
