import cv2
import numpy as np
from RotationMatrix import rotationMatrix

def dsts(x1,y1,x0=0,y0=0):
    return (x1-x0)**2 + (y1-y0)**2


def rotate(rotation,Xp,Yp):
    Xr=Xp/np.cos(rotation[0])## I have not yet set the base system to evaluate
    Yr=Yp/np.cos(rotation[1])## I have not yet set the base system to evaluate
    Xt = np.cos(rotation[2])*Xr - np.sin(rotation[2])*Yr
    Yt = np.sin(rotation[2])*Xr + np.cos(rotation[2])*Yr
    return Xt,Yt

def absoluteCoordinate(data):
    size,image_points = data[0],data[1]
    X=size[0]
    Y=size[1]
    midx=X//2
    midy=Y//2
    mini=[image_points[0][0],image_points[0][1]]
    Yp=midy-mini[1]
    Xp=midx-mini[0]
    Xrefy=image_points[1][0]-mini[0]
    Yrefy=image_points[1][1]-mini[1]
    Xrefx=image_points[2][0]-mini[0]
    Yrefx=image_points[2][1]-mini[1]
    rotation,_ = rotationMatrix(size,image_points)
    Xt,Yt=rotate(rotation,Xp,Yp)
    Xrefxt,Yrefxt=rotate(rotation,Xrefx,Yrefx)
    Xrefyt,Yrefyt=rotate(rotation,Xrefy,Yrefy)
    print(Xrefxt,Yrefyt)
    Xt *= 1920/np.sqrt(dsts(Xrefxt,Yrefxt))
    Yt *= 1080/np.sqrt((dsts(Xrefyt,Yrefyt)))
    return Xt,Yt

if __name__=="__main__":
    exit()
