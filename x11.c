#include <X11/X.h>
#include <X11/Xlib.h>

int main(void) {
  Display *dpy = XOpenDisplay(NULL);
  if (!dpy)
    return 1;

  int screen = DefaultScreen(dpy);
  Window root = RootWindow(dpy, screen);

  Window win =
      XCreateSimpleWindow(dpy, root, 10, 10, 400, 300, 2,
                          BlackPixel(dpy, screen), WhitePixel(dpy, screen));

  XStoreName(dpy, win, "x11 window");

  XSelectInput(dpy, win, StructureNotifyMask);

  XMapWindow(dpy, win);

  XEvent ev;

  while (1) {
    XNextEvent(dpy, &ev);
    if (ev.type == MapNotify) {
      break;
    }
  }

  XNextEvent(dpy, &ev);

  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  return 0;
}
