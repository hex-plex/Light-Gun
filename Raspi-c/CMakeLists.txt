cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(LightGun VERSION 0.8)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(OpenCV REQUIRED)
# set(OpenCV_DIR /usr/local/lib/cmake/opencv4)
# set(OpenCV_INCLUDE_HEAD /usr/local/include)
# set(OpenCV_LIBS /usr/local/include/lib)
# add the executable
include_directories(${OpenCV_INCLUDE_HEAD}/opencv)
include_directories(${OpenCV_INCLUDE_HEAD}/opencv2)
include_directories(${OpenCV_INCLUDE_HEAD}/opencv4)

include_directories(
  include
)

# include_directories()

# add_executable(LightGun src/main.cpp)
# target_link_libraries(LightGun ${OpenCV_LIBS})

# install(TARGETS LightGun DESTINATION bin)

add_subdirectory(src)
