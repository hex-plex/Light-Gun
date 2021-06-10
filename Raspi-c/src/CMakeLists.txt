add_executable(LightGun main.cpp)
target_link_libraries(LightGun ${OpenCV_LIBS})
add_executable(CamCalibrate cameraCalibrationOnce.cpp)
target_link_libraries(CamCalibrate ${OpenCV_LIBS})
add_executable(ScreenCalibrate PointCalibration.cpp)
target_link_libraries(ScreenCalibrate ${OpenCV_LIBS})

install(TARGETS LightGun DESTINATION bin)
