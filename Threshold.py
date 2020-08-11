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
    lowgreen = np.array([ 30, 139, 166])
    highgreen = np.array([ 36, 255, 234])
    mask=cv2.inRange(img,lowgreen,highgreen)
    kernel = np.array([5,5],dtype=np.uint8)
    mask= cv2.dilate(mask,kernel,iterations = 6)
    contour,heirarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contheir=zip(contour,np.squeeze(heirarchy))
    sortList = sorted(contheir,key=lambda x: cv2.contourArea(x[0]),reverse=True)
    temp=[]
    epsilon=0.4*cv2.contourArea(sortList[0][0])
    for cnt,heir in sortList:
        if heir[-1]!=-1: 
            continue # This to save us from some overlapping detected ones to remove with heirarchy
        if len(temp)==0:
            temp.append(cnt)
        elif len(temp)>4:
            temp=[]
        elif cv2.contourArea(temp[0])-epsilon <= cv2.contourArea(cnt) <= cv2.contourArea(temp[0])+epsilon:
            temp.append(cnt)
        

    ## This is being done so that we can thres only similar looking contour
    ## But later a ir led can be fit in the center
    if len(temp)<4:
        raise Exception("The contour could not be found on the screen")
    temp = temp[:4] # This is again not a good method
    final = 4*[0]
    for i in range(len(temp)):
        cir,_ =  cv2.minEnclosingCircle(temp[i])
        final[i] = np.array([int(cir[0]),int(cir[1])])
    final  = sorted(final,key = lambda x : dst(x[0],x[1]) )
    return img.shape , final


if __name__=="__main__":
    exit()
