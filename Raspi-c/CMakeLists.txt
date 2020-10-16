cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(LightGun VERSION 0.8)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(LightGun src/main.cpp)
add_executable(CamCalibrate src/cameraCalibrationOnce.cpp)
add_executable(ScreenCalibrate src/PointCalibration.cpp)