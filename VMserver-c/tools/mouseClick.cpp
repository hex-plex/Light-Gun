#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

void mouseClick(Display* display, int button, int x, int y){
	Window root = DefaultRootWindow(display);
	XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);

	XTestFakeButtonEvent(display,Button1, true, 0);
	XFlush(display);
	usleep(100000);

	XTestFakeButtonEvent(display, Button1, false, 0);

	XFlush(display);
}

int main(int argc,char* argv[]){
	int x,y;
	x = atoi(argv[1]);
	y = atoi(argv[2]);

	Display *display = XOpenDisplay(0);	
	mouseClick(display, Button1, x, y);
	XFlush(display);
	XCloseDisplay(display);
	return 0;
}