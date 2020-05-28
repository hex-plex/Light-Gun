import pythoncom, pyHook

def OnKeyboardEvent(event):
    print(event.Key=='H')
    print('---')

# return True to pass the event to other handlers
    return False

# create a hook manager
hm = pyHook.HookManager()
# watch for all mouse events
hm.KeyDown = OnKeyboardEvent
# set the hook
hm.HookKeyboard()
# wait forever
#pythoncom.PumpMessages()
