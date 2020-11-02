#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

void mouseClick(int button){
	Display *display = XOpenDisplay(0);
	
	XTestFakeButtonEvent(display,Button1, true, 0);
	XFlush(display);
	usleep(100000);

	XTestFakeButtonEvent(display, Button1, false, 0);
	/*
	XEvent event;

	if(display == NULL){
		fprintf(stderr,"Cannot initialize the display \n");
		exit(EXIT_FAILURE);
	}

	memset(&event,0x00, sizeof(event));

	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;

	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while(event.xbutton.subwindow){
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);	
	}
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)fprintf(stderr,"Error \n");
	XFlush(display);
	usleep(10000);

	event.type = ButtonRelease;
	event.xbutton.state = 0x100;

	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)fprintf(stderr,"Error \n");
	*/
	XFlush(display);

	XCloseDisplay(display);	
}

int main(int argc,char* argv[]){
	int x,y;
	x = atoi(argv[1]);
	y = atoi(argv[2]);

	Display *display = XOpenDisplay(0);

	Window root = DefaultRootWindow(display);
	XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
	mouseClick(Button1);
	XFlush(display);
	XCloseDisplay(display);
	return 0;
}