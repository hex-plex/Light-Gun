import cv2
import numpy as np
import _thread
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
        self.acServer = actionServer
        self.acServer()
        
    def __repr__(self):
        return "<< Maincore: Processes "+str(self.count)+" >>"
    
    def capture(self,flag):
        while flag:
            if self.acServer.actionInput():
                frame=self.feedline.read()[1]
                self.thresholdJob.append(frame)
        ## this only works when a certain key is pressed set at actionInput
    def projectionWork(self,flag):
        while flag:
            if len(self.projectionJob)!=0:
                try:
                    X,Y=absoluteCoordinate(self.projectionJob[0])
                    del self.projectionJob[0]
                    self.actionJob.append([X,Y])
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
        while flag:
            if len(self.actionJob)!=0:
                if self.acServer.actionGUI(self.actionJob[0]):
                    del self.actionJob[0]
                    self.count+=1
        ## Have to complete the action methods
    def thresholdWork(self,flag):
        while flag:
            if len(self.thresholdJob)!=0:
                try:
                    size,image_points=threshold(self.thresholdJob[0])
                    del self.thresholdJob[0]
                    self.projectionJob.append((size,image_points))
                except Exception as nfe:
                    print(nfe)
                    time.sleep(5)
                    exit()
        ## this gonna give the needed points to process
    def collectGarbage(self,flag):
        while flag:
            if self.count%10==1:
                gc.collect()
    ## This is to free up ram periodically
            
    def __call__(self):
        if not self.flag:
            self.flag=1
            _thread.start_new_thread(self.capture,(self.flag,))  ## The threading allows to paralely use more cores if available
            _thread.start_new_thread(self.projectionWork,(self.flag,)) ## Hence helping my code to run efficently
            _thread.start_new_thread(self.actionWork,(self.flag,))
            _thread.start_new_thread(self.thresholdWork,(self.flag,))
            _thread.start_new_thread(self.collectGarbage,(self.flag,))
            self.inittime = time.time()
            return "Started the run"
        else:
            return "The application is runnig for "+str(time.time()-self.inittime)+" s"
       
"""
if __name__=="__main__":
    cap=cv2.VideoCapture("http://192.168.43.1:8080/video")
    a = ActionServer()
    obj = MainCore(cap,a)
    print(obj())
"""
## Example usage

if __name__=="__main__":
    exit()
    
            
        
