import cv2
import numpy as np

cap = cv2.VideoCapture(0)
img=cap.read()[1]
r=cv2.selectROI(img)
imp=img[r[1]:r[1]+r[3],r[0]:r[0]+r[2]]
low=np.array([imp[:,:,0].min(),imp[:,:,1].min(),imp[:,:,2].min()])
high=np.array([imp[:,:,0].max(),imp[:,:,1].max(),imp[:,:,2].max()])

mask = cv2.inRange(img,low,high)
cv2.imshow("all the points",mask)
cv2.waitKey(0)
