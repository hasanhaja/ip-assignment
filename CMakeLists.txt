cmake_minimum_required(VERSION 3.16)
project(ip_assignment)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(ip_assignment src/main.cpp src/part_a/encoder.cpp src/part_a/decoder.cpp src/part_b/encoder.cpp)

target_link_libraries(ip_assignment ${OpenCV_LIBS})