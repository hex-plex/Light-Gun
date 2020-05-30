import numpy as np
import cv2
from Threshold import threshold
def configFrame(img):
    
        _,thrimgpoints=threshold(img)
        for cor in thrimgpoints:
            cv2.circle(img,(cor[0],cor[1]),5,(0,255,0),2)
        cv2.imshow("config",img)
        cv2.waitKey(0)
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
        cv2.destroyAllWindows()
        return True
        '''
except:
        print("Config failed try to manually doing it")
        cv2.destroyAllWindows()
        return False
    '''
               
if __name__=="__main__":
    cap=cv2.VideoCapture("http://192.168.43.1:8080/video")
    frame=cap.read()[1]
    configFrame(frame)
