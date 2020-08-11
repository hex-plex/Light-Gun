import pyautogui as pyg
from pyHook import HookManager
import time
import _thread

class ActionServer():
    ## While initializing set the key you want to use to trigger
    def __init__(self,char='F'):
        self.buffer=[]
        self.Key__t=char
        self.flag=0
        self.hm = HookManager()
        
    def actionRead(self,event):
        if event.Key==self.Key__t:
            self.buffer.append(time.time())
        return True
            
    ## This cannot be used as it cant get background key inputs
    ## This would act like a asynchronous server as it has to be
    def actionInput(self):
        if len(self.buffer)==0:
            return False
        while (len(self.buffer)!=0):
            if (time.time()-self.buffer[0]) < 0.5 :
                del self.buffer[0]
                return True
            del self.buffer[0]
        return False

    def actionGUI(self,coor):
        try :
            pyg.click(coor[0],coor[1])
            return True
        except:
            return False

    def __call__(self):
        if not self.flag:
            self.flag=1
            #_thread.start_new_thread(self.actionRead,())
            self.hm.KeyDown = self.actionRead
            self.hm.HookKeyboard()
            print("The server is running")
        else:
            print("Server is already running")
        
