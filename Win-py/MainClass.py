import cv2
import numpy as np
import threading
import time
import gc
from Projection import absoluteCoordinate
from Threshold import threshold
from Action import ActionServer
from PointConfig import configFrame
class MainCore():
    thresholdJob=[]
    projectionJob=[]
    actionJob=[]
    count=0
    flag=0
    def __init__(self,captureModule=None,actionServer=None):
        self.feedline = captureModule
        self.inittime = time.time()
        self._count=1
        self.acServer = actionServer
        self.acServer()
        
    def __repr__(self):
        return "<< Maincore: Processes "+str(self.count)+" >>"
    
    def capture(self,flag):
        frame=self.feedline.read()[1]
        self.thresholdJob.append(frame)
        T = threading.thread(target=self.thresholdWork,args=(True,))
        T.start()
        ## this only works when a certain key is pressed set at actionInput
    def projectionWork(self,flag):
        while flag and len(self.projectionJob)!=0:
            try:
                projection = self.projectionJob.pop(0)
                X,Y=absoluteCoordinate(projection)
                self.actionJob.append([X,Y])
                t = threading.thread(target=self.actionWork, args=(True,))
            except Exception as nce:
                print(nce)
                print("Starting the config process")
                print("Keep the frame straight perpendicular to vision")
                print("in 3..",end="")
                time.sleep(1)
                print("2..",end="")
                time.sleep(1)
                print("1..",end="")
                time.sleep(1)
                print("0")
                frame = self.feedline.read()[1]
                if configFrame(frame):
                    print("Config Complete Succesfully")
                else:
                    time.sleep(3)
                    exit()
                                        
        ## works the same way 
    def actionWork(self,flag):
        while flag and len(self.actionJob)!=0:
            act = self.actionJob.pop(0)
            if self.acServer.actionGUI(act):
                self.counter = self._count+1
            else:
                self.actionJob.insert(0)
        return True
        ## Have to complete the action methods
    def thresholdWork(self,flag):
        if len(self.thresholdJob)!=0:
            try:
                thresh = self.thresholdJob.pop(0)
                size,image_points=threshold(thres)
                self.projectionJob.append((size,image_points))
                t = threading.thread(target=self.projectionWork, args=(True,))
                t.start()
            except Exception as nfe:
                print(nfe)
                time.sleep(5)
                exit()
        ## this gonna give the needed points to process
    def collectGarbage(self,flag):
        gc.collect()
    ## This is to free up ram periodically but rather a more complicated approach can be taken
    @property
    def counter(self):
        return self._count

    @counter.setter
    def set_count(self,new_value):
        if new_value%10==0:
            t = threading.thread(target=self.collectGarbage,args=(True,))
            t.start()
        self._count=new_value
        
    def __call__(self):
        if not self.flag:
            self.flag=1
            self.acServer._callbacks.append(self.capture)
            self.inittime = time.time()
            return "Started the run"
        else:
            return "The application is runnig for "+str(time.time()-self.inittime)+" s"
       

if __name__=="__main__":
    cap=cv2.VideoCapture("http://192.168.43.1:8080/video")
    a = ActionServer()
    obj = MainCore(cap,a)
    print(obj())
    while True:
        pass
## Example usage
if __name__=="__main__":
    exit()
    
            
        
