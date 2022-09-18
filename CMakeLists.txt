cmake_minimum_required(VERSION 3.23)
project(cpp_segment)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_segment main.cpp)
add_subdirectory(GetMachineInfo)
add_subdirectory(pointcloud_tools)
