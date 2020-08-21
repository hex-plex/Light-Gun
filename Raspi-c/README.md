# LIGHT-GUN
This is configured to work with raspberry pi to have the device usable and plug and play kind accross all platforms (this also helps me achive the goal of the project).

## Configure Camera
Configuration here can be split into three part
- Distortion and Transformation of the camera
- Auto white balance, ISO and temperature control
- The point mapping of the leds to the display
## Distortion and Transformation of the Camera
Run the cameraCalibrateOnce.cpp to get the Distortion and Transformation matrix of the camera and will store this into a file which can be reused accross all operations. You would need to have Checkerboard to configure this which is a little inconvenient but is a neccesary step. But one could approximate the same if and only if they dont have a lens attached to the camera which skewes ( You can look for the approximation in the Python scripts or visit the link in the main README).
## Auto white Balance, ISO and temperature control
This step is important to keep the thresholding values consistent over all the runs. You can use OpenCV directly to SET these values of the camera parameter.<br/>
Ex:- <br/>
```python
cap.set(cv::CAP_PROP_BRIGHTNESS,50);
```
many more parameters can be seen in OpenCV docs<br/>
But , This rather doesnt work well with all the hardware types and a lot of times fails to fetch the camera api one has.<br/>
The best solution is to use the Linux Kernel which the Camera uses, mostly it is V4L(VideoForLinux).<br/>
you can check it out as follows

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
## The point mapping
Run the PointCalibration.cpp to get the mapping store do note have the camera as parallel to the screen as possible .
