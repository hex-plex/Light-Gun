cmake_minimum_required(VERSION 3.10)

project(VMserver VERSION 0.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package()

add_executable(VMserver src/vmlaunch.cpp)
# target_link_libraries(VMserver ${})
