import cv2
import numpy as np

def dst(x1,y1,x0=0,y0=0):
    return (x1-x0)**2 + (y1-y0)**2

def threshold(img):
    #This piece should threshold the four corners as image_points
    #as i have not been able to devise any method to do it consitently i am leaving it blank for now
    #green cutouts with ir led in them for thresholding and centers to match
    #This should be a good method rather than the normal ir
    #Else the aruco markers are good choice but they are computationally expensive
    #default
    img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    lowgreen = np.array([0,0,0]) ## This is to be set yet
    highgreen = np.array([0,0,0]) ## even this
    mask=cv2.inRange(img,lowgreen,highgreen)
    kernel = np.ones((5,5),np.uint8)
    mask=cv2.erode(mask,kernel)
    mask=cv2.GaussianBlur(mask,ksize=5)
    mask=cv2.erode(mask,kernel)
    mask=cv2.GaussianBlur(mask,ksize=5)
    contours, hierarchy = cv.findContours(mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    sortList = sorted(contours,key=cv2.contourArea,reverse=True)
    temp=[]
    for cnt in sortList:
        if len(temp)==0:
            temp.append(cnt)
        elif len(temp)>4:
            temp=[]
        elif cv2.contourArea(temp[0])-epsilon <= cv2.contourArea(cnt) <= cv2.contourArea(temp[0])+epsilon:
            temp.append(cnt)

    ## This is being done so that we can thres only similar looking contour
    ## But later a ir led can be fit in the center
    if len(temp)<4:
        raise NotFoundError("The contour could not be found on the screen")
    final  = sorted(temp[:4],key=lambda(x: dst(x[0],x[1])))
    return img.shape , np.array(final,dtype=np.uint8)


if __name__=="__main__":
    exit()
