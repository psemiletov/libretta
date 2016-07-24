#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
 
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <cstring>

#include "libretta_img_utils.h"
#include "libretta_img_tga.h"


using namespace std;



int main (int argc, const char* argv[]) 
{
  if (argc == 0)
    return 0;
 
 
  CTGAImage image (argv[1]);
  char *rgba = rgb_to_rgba (image.data_rgb, image.tga_header.width, image.tga_header.height);

  
  Display *display = XOpenDisplay (0);
  if (! display)
     return 0;

  int blackColor = BlackPixel (display, DefaultScreen(display));
  int whiteColor = WhitePixel (display, DefaultScreen(display));

  Window w = XCreateSimpleWindow (display, DefaultRootWindow (display), 0, 0, 
				  800, 600, 0, blackColor, blackColor);

  XSelectInput(display, w, ExposureMask | KeyPressMask);

  Atom WM_DELETE_WINDOW = XInternAtom (display, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(display, w, &WM_DELETE_WINDOW, 1);  

  XMapWindow (display, w);

  Visual *visual = DefaultVisual (display, 0);
  
  XResizeWindow (display, w, image.tga_header.width, image.tga_header.height);
  
  XImage *ximg = XCreateImage (display, visual, 24, ZPixmap, 0, rgba, image.tga_header.width, image.tga_header.height, 32, 0);
  
  if (! ximg)
    {
     cout << "! ximg" << endl;  
     XDestroyWindow (display, w);
     XCloseDisplay (display);
    }
  
      
  XEvent e;
  while (1) 
        {
         XNextEvent (display, &e);
	 
         if (e.type == Expose) 
            XPutImage (display, w, DefaultGC (display, 0), ximg, 0, 0, 0, 0, image.tga_header.width, image.tga_header.height);
    
         if (e.type == KeyPress)
            {
             char buf[128] = {0};
             KeySym keysym;
             XLookupString (&e.xkey, buf, sizeof buf, &keysym, NULL);
             if (keysym == XK_Escape)
                break;
            }
 
         if ((e.type == ClientMessage) && 
            (static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
            break;
     
         }
      
  XDestroyWindow (display, w);
  XCloseDisplay (display);
  
  delete [] rgba;
  
  return 0;
}