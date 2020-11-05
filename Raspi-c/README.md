# LIGHT-GUN
This is configured to work with raspberry pi to have the device usable and plug and play kind accross all platforms (this also helps me achive the goal of the project).

## Configure Camera
Configuration here can be split into three part
- Distortion and Transformation of the camera
- Auto white balance, ISO and temperature control
- The point mapping of the leds to the display

## Installation
_Before running any Application <a href="#PreInstallation">checkout</a> the ISO, temp control as to reduce variance as much as possible._
#### Raspberry Pi
There are few dependencies that are neccesary for building the project.
###### Pre Installation
```bash
Opencv
Bluez
WiringPi
```
###### Build Project
``` bash
git clone https://github.com/hex-plex/Light-Gun
cd Light-Gun/Raspi-c
mkdir -p build && cd build
cmake ../
cmake --build .
./CamCalibrate                    ## To calibrate the camera module and attain its distcoeff and camera matrix
./ScreenCalibrate                 ## To Calibrate the pose of the leds and map them with edges of display
echo "e9:eb:d6:a8:0b:af" >> .configDevice  ## Host devices bluetooth Address to connect.
./LightGun                        ## To run the Application
```
#### Local Machine
``` bash
git clone https://github.com/hex-plex/Light-Gun
cd Light-Gun/VMserver-c
mkdir -p build && cd build
### If Linux
sudo apt-get install libx11-dev libx11tst-dev
### or If windows
### install autogui library for cmake.
cmake ../
cmake --build .
./VMserver                        ## This will launch the server on the local host
```

## Camera Calibrations
### Distortion and Transformation of the Camera
Run the CamCalibrate application to get the Distortion and Transformation matrix of the camera and will store this into a file which can be reused accross all operations. You would need to have Checkerboard to configure this which is a little inconvenient but is a neccesary step. But one could approximate the same if and only if they dont have a lens attached to the camera which skewes ( You can look for the approximation in the Python scripts or visit the link in the main README).
### Auto white Balance, ISO and temperature control
This step is important to keep the thresholding values consistent over all the runs. You can use OpenCV directly to SET these values of the camera parameter.<br/>
Ex:- <br/>
```C++
cap.set(cv::CAP_PROP_BRIGHTNESS,20);
```
many more parameters can be seen in OpenCV docs<br/>
But , This rather doesnt work well with all the hardware types and a lot of times fails to fetch the camera api one has.<br/>
The best solution is to use the Linux Kernel which the Camera uses, mostly it is V4L(VideoForLinux).<br/>
you can check it out as follows
#### PreInstallation
```bash
sudo apt-get install v4l-utils
v4l2-ctl --list-devices  ## This would show you all the devices registered under the api
v4l2-ctl -d /dev/video0 --list-ctrls | less
echo "This would list all the controls your camera can be operated with."
```
Your controls may very from mine but there would be equivalent controls in most of the camera modules.
```bash
v4l2-ctl --set-ctrl=white_balance_auto_preset=0 ## This removes the auto configuration of white Balance
echo "The parameters below are very specific to the hardware and ones liking and doesnt make any major impact"
v4l2-ctl --set-ctrl=blue_balance=1500
v4l2-ctl --set-ctrl=red_balance=1200
v4l2-ctl --set-ctrl=sharpness=50
```
If you change your hardware frequently then you can add these into ~/.profile or even ~/.bashrc (if one chooses to use the setting only in the terminal)
```bash
echo "v4l2-ctl --set-ctrl=white_balance_auto_preset=0" >> ~/.profile
```
And so on as one wants to implement these.


The configuration should start working by now and should start responding to each button clicks.
### Point mapping
Run the ScreenCalibrate application to get the mapping stored. do note that the camera must be parallel to the screen as much as possible.
