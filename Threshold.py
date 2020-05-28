import cv2
import numpy as np

def threshold(img):
    #This piece should threshold the four corners as image_points
    #as i have not been able to devise any method to do it consitently i am leaving it blank for now
    #green cutouts with ir led in them for thresholding and centers to match
    #This should be a good method rather than the normal ir
    #Else the aruco markers are good choice but they are computationally expensive
    #default
    return img.shape,np.array([[0,0]])


if __name__=="__main__":
    exit()
