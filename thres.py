import cv2
import numpy as np

cam = cv2.VideoCapture("http://192.168.43.1:8080/video")

low=np.array([149,20,150])## This detects the ir led found in my tv remote but can t be used to do so any setup
high=np.array([151,50,255])

while True:
    frame = cam.read()[1]
    frame=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    mask=cv2.inRange(frame,low,high)
    cv2.imshow("hello",mask)
    cv2.waitKey(1)
