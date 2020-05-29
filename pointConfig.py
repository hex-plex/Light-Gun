import numpy as np
import cv2
from Threshold import threshold
def configFrame(img):
    try:
        _,thrimgpoints=threshold(img)
        for cor in thrimgpoints:
            cv2.circle(img,(cor[0],cor[1]),5,(0,255,0),2)
        cv2.imshow("config",img)
        print("Set the points irrespective of the thresholded points")
        r = cv2.selectROI(img)
        actualPoints=np.array([ [ r[1] , r[0] ] , [ r[1]+r[3] , r[0] ] , [ r[1] , r[0]+r[2] ] , [ r[1]+r[3] , r[0]+r[2] ] ])
    ## This is so that the relative error of placement of stickers should not cause any error
    ## For simplicity now i will use the one with only thresholded center
    ## Though we would any way use the threspoint as modelpoints
    ## But the points after threshold the relative positioning should be done so that
    ## its mapped to the actualPoints hence the precise position is found
        np.savetxt("modelPoints.xyz",thrimgpoints,delimiter=",")
        np.savetxt("precPoints.xyz",actualPoints,delimiter=",")
        return True
    except:
        print("Config failed try to manually doing it")
        return False
    
               
