## Light-Gun
This Folder contains the code for testing out the basic concepts of my project. It is been implemented in python. The code is not optimized and calibrated correctly and only works in a specific ligting condition. The code is been ported and revised to C++, which is done to help in a being computationally lighter for a single board computer.<br/>
## Glimpse:
### **This is totally outdated, new updates are on there way**

Initialize the MainCore Server with the the objects and parameters needed
```python
from MainClass import MainCore  ## This Runs the real code
from Action import ActionServer ## This server is to register action from keyboard and to take action as a mouse
import cv2  

cap = cv2.VideoCapture(1)  ## This could be any external video feed for detection
act = ActionServer('F')    ## Initializing the server with a key here 'F' would be the trigger by default its 'F' you can setit to any key on keyboard
obj = MainCore(cap,act)    ## Initializing with the camera object (cap) and the ActionServer object (act)
obj()                      ## This will start the server
```

To Check for how long the server is been running
```python
print(obj()) ## This display for how long the server been running
```
One can change the example usage and use it directly for their use case
and run the MainClass.py as I did
![Setup](https://raw.githubusercontent.com/hex-plex/Light-Gun.apk/master/images/working_with_manual_scalling.jpg)

For Configuring the thresholding points that is the green cut outs in my case you can use the red thres to find the range
and and then use PointConfig to configure them as follows
```python
from PointConfig import configFrame
import cv2

cap = cv2.VideoCapture(1) ## Reference of any external Camera
frame =cap.read()[1]      ## Fetching a perpendicular viewed frame of the screen
configFrame(frame)        ## Starting the configuration process
```
After configuration the program while work once the scalling is set which would be in the next update

**This is a demo of the program by putting a manual scalling to the cursor coordinates**
![Working demo](https://raw.githubusercontent.com/hex-plex/Light-Gun.apk/master/images/working_with_manual_scalling2.jpg)

## **The code may not work as expected hence I suggest using the Raspi-c folder.**

### Flaws
- The rotation matrix is not used instead rvec was used in code. Later changed it by using cv2.Rodrigues.
- The Point 2 Point mapping of the pointers and the display corners are not done. This is been updated in C++ side of the code taking a difference of the pointer vector and the pointer2corner vector.
- The Scale is not set. Updated in c++ code so that the display could be of any resolution and the code would  make actions based on it
- The Thresholding of coloured objects are challenging and light dependent. This replaced by IR Leds in the C++ code so as to make thresholding easier as they are sources of light themselves.
- Action Registration was done by listenning to all the key strokes on a seperate thread which is runs on the CPU all the time. Its been replaced with **Hardware Interrupt** to save a lot of CPU time.
- No Adaptive Thresholding , updated on the c++ side.
