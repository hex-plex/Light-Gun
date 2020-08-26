# Light-Gun

## This is to create a light gun using Opencv and camera module of a android mobile
Bored in the quarantined period revisiting my old video games with light gun inspired a idea of light gun in lcd monitors , I went on building it mainly as a android package as it would be accessable for any one. Then ended up using a Raspberry Pi as a standalone device to able to use it accross platforms and devices.<br/>
**Raspi-c is the main working directory for now.**
## Contribution
Any kind of Contribution is always welcomed. The rules for any Contribution for now is vague as I have not really structurized the project so well as mostly its in the development period, So its prone to some nasty errors(Anyways feel free to report it :smile: ), Any Idea for a better implementation is also welcome.
## ToDo:
- Put a camera module in a toy gun to get the feed from there. (for now i used my phones camera module in demo)
- Devise a method to convert the HSV color space into a grayscale which measures how close is it to the color of the leds in ideal condition. This is very useful in adaptive thresholding.
- Work out the problems with **Hardware Interrupts** and make a communication protocol between the Pi and the Computer.
- ><del>Convert the code into java based android package for any one to use.</del><br/>
This is not the main motive now

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

## Reference:
- This is for getting R and t matrix  https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/
- This is for adjusting focal length (approximation) https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/
- The best solution is to create some software to make some kind of points on to the screen all along the run
- Basic structure completed with multithreading to split the work and decrease latency
