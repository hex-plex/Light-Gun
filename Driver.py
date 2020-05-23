import cv2
import numpy

from MainClass import MainCore
from Action import ActionServer
def main():
    cap=cv2.VideoCapture(0)
    a=ActionServer()
    obj=MainCore(cap,a)
    print(obj())

if __name__=="__main__":
    main()
