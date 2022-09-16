project(cpp_segment)

set(CMAKE_CXX_STANDARD 14)

add_executable(getcpuid main.cpp GetMachineID.cpp GetMachineID.h)
target_link_libraries(getcpuid -luuid)
