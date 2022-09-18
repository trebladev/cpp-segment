project(cpp_segment)

set(CMAKE_CXX_STANDARD 14)

find_package(PCL REQUIRED)
#find_package(Threads)
include_directories(${PCL_INCLUDE_DIR})

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(mesh2ply mesh2ply.cpp)
target_link_libraries(mesh2ply ${PCL_LIBRARIES})