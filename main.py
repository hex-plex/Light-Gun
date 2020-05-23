import cv2
import numpy as np
import _thread
import time
import gc
from Projection import absoluteCoordinate
from Threshold import threshold
class MainCore():
    thresholdJob=[]
    projectionJob=[]
    actionJob=[]
    count=0
    flag=0
    def __init__(self,cap):
        self.feedline = cap
        self.inittime = time.time()
        
    def __repr__(self):
        return "<< Maincore: Processes "+str(self.count)+" >>"
    
    def capture(self,flag):
        while flag:
            if actionInput():
                frame=self.feedline.read()[0]
                self.thresholdJob.append(frame)

    def projectionWork(self,flag):
        while flag:
            if len(self.projectionJob)!=0:
                X,Y=absoluteCoordinate(self.projectionJob[0])
                del self.projectionJob[0]
                self.actionJob.append([X,Y])

    def actionWork(self,flag):
        while flag:
            if len(self.actionJob)!=0:
                if actionGUI(self.actionJob[0]):
                    del self.actionJob[0]
                    self.count+=1
                
    def thresholdWork(self,flag):
        while flag:
            if len(self.thresholdJob)!=0:
                image_points=threshold(self.thresholdJob[0])
                del self.thresholdJob[0]
                self.projectionJob.append(image_points)

    def collectGarbage(self,flag):
        while flag:
            if self.count%10==1:
                gc.collect()
    ## This is to free up ram
            
    def __call__(self):
        if not self.flag:
            self.flag=1
            _thread.start_new_thread(self.capture,(self.flag))
            _thread.start_new_thread(self.projectWork,(self.flag))
            _thread.start_new_thread(self.actionWork,(self.flag))
            _thread.start_new_thread(self.thresholdWork,(self.flag))
            _thread.start_new_thread(self.collectGarbage,(self.flag))
            self.inittime = time.time()
            return "Started the run"
        else:
            return "The application is runnig for "+str(time.time()-inittime)+" s"
        
if __name__=="__main__":
    cap=cv2.VideoCapture(0)
    obj = MainCore(cap)
    print(obj())
    
    
    
            
        
