# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Light-Gun/Raspi-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Light-Gun/Raspi-c/build

# Include any dependencies generated for this target.
include CMakeFiles/CamCalibrate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CamCalibrate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CamCalibrate.dir/flags.make

CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o: CMakeFiles/CamCalibrate.dir/flags.make
CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o: ../src/cameraCalibrationOnce.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Light-Gun/Raspi-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o -c /home/pi/Light-Gun/Raspi-c/src/cameraCalibrationOnce.cpp

CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Light-Gun/Raspi-c/src/cameraCalibrationOnce.cpp > CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.i

CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Light-Gun/Raspi-c/src/cameraCalibrationOnce.cpp -o CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.s

# Object files for target CamCalibrate
CamCalibrate_OBJECTS = \
"CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o"

# External object files for target CamCalibrate
CamCalibrate_EXTERNAL_OBJECTS =

CamCalibrate: CMakeFiles/CamCalibrate.dir/src/cameraCalibrationOnce.cpp.o
CamCalibrate: CMakeFiles/CamCalibrate.dir/build.make
CamCalibrate: /usr/local/lib/libopencv_gapi.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_stitching.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_aruco.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_bgsegm.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_bioinspired.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_ccalib.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_dnn_objdetect.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_dpm.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_face.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_freetype.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_fuzzy.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_hdf.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_hfs.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_img_hash.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_line_descriptor.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_quality.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_reg.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_rgbd.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_saliency.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_stereo.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_structured_light.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_superres.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_surface_matching.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_tracking.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_videostab.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_xfeatures2d.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_xobjdetect.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_xphoto.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_shape.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_datasets.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_plot.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_text.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_dnn.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_highgui.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_ml.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_phase_unwrapping.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_optflow.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_ximgproc.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_video.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_videoio.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_imgcodecs.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_objdetect.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_calib3d.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_features2d.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_flann.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_photo.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_imgproc.so.4.1.1
CamCalibrate: /usr/local/lib/libopencv_core.so.4.1.1
CamCalibrate: CMakeFiles/CamCalibrate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Light-Gun/Raspi-c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CamCalibrate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CamCalibrate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CamCalibrate.dir/build: CamCalibrate

.PHONY : CMakeFiles/CamCalibrate.dir/build

CMakeFiles/CamCalibrate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CamCalibrate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CamCalibrate.dir/clean

CMakeFiles/CamCalibrate.dir/depend:
	cd /home/pi/Light-Gun/Raspi-c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Light-Gun/Raspi-c /home/pi/Light-Gun/Raspi-c /home/pi/Light-Gun/Raspi-c/build /home/pi/Light-Gun/Raspi-c/build /home/pi/Light-Gun/Raspi-c/build/CMakeFiles/CamCalibrate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CamCalibrate.dir/depend

