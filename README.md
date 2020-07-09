# Light-Gun 

## This is to create a light gun using Opencv and camera module of a android mobile
Bored in the quarantined period seeing my old video game with light gun inspired a idea of light gun in lcd monitors , I went on building it mainly as a android package as it would be accessable for any one.
>For now I have implemented on python using my phones camera module 

## ToDo:
- Configure the camera for more acurate measurements.
- Scale the input screen coordinates with respect to the actual coordinates
- Utilize the precCoor to project or clip in the actual plane rather than 
- Put a camera module in a toy gun to get the feed from there. (for now i used my phones camera module in demo)
- Use the **relative thresholding** to make a better estimate of the detection contours(This is consider something white on the screen and then threshold the color on basis of **Color-White** rather than the **Color** itself as then it would clear up most of the change in lighting scenario)
- Use the ir leds to be sure to not be thresholding any other contour
- Trying to port this on python for prototyping it well on raspberry pi and then start working on mobile as its not very hand on mobile but a good encloser and trigger should work well with the android app
- Convert the code into java based android package for any one to use.

## Glimpse:
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

  
