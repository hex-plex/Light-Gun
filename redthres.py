import cv2
import numpy as np

img = cv2.imread("headPose.jpg")

print(img.shape)
points=[(534,432)]

for point in points:
    cv2.circle(img,point,1,(255,0,0),2)
    cv2.imshow("frame",img)
    cv2.waitKey(0)
