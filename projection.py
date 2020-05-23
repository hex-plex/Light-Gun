import cv2
import numpy as np
from RotationMatrix import rotationMatrix

def dsts(x1,y1,x0=0,y0=0):
    return (x1-x0)**2 + (y1-y0)**2

def absoluteCoordinate(size,image_points):
    X=size[0]
    Y=size[1]
    midx=X//2
    midy=Y//2
    mini=[image_points[0][0],image_points[0][1]]
    for coor in image_points[1:]:
        if dsts(coor[0],coor[1])<dsts(mini[0],mini[1]):
            mini[0],mini[1]=coor[0],coor[1]

    Yp=midy-mini[1]
    Xp=midx-mini[0]
    rotation = rotationMatrix(img.shape,image_points)
    Xr=Xp/np.cos(rotation[0])## I have not yet set the base system to evaluate
    Yr=Yp/np.cos(rotation[1])## I have not yet set the base system to evaluate
    Zr = complex(Xr,Yr)
    Zr *= np.exp(complex(0,rotation[2]))  ## This computationally superior to other methods as numpy optimizes it very well
    Xr = np.real(Zr)
    Yr = np.imag(Zr)   ## I have not yet set the base system to evaluate
    return Xr,Yr
    
            
if __name__=="__main__":
    exit()
