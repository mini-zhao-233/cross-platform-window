#include <X11/X.h>
#include <X11/Xlib.h>

int main(void) {
  // 连接显示服务器
  Display *dpy = XOpenDisplay(NULL);
  if (!dpy)
    return 1;

  // 获取默认显示器
  int screen = DefaultScreen(dpy);
  //获取根窗口
  Window root = RootWindow(dpy, screen);

  //创建新窗口
  Window win =
      XCreateSimpleWindow(dpy, root, 10, 10, 400, 300, 2,
                          BlackPixel(dpy, screen), WhitePixel(dpy, screen));

  //窗口的标题
  XStoreName(dpy, win, "x11 window");

  //监听窗口结构变化相关的事件
  XSelectInput(dpy, win, StructureNotifyMask);

  //映射窗口，使其可见
  XMapWindow(dpy, win);

  XEvent ev;

  //当窗口显示出来后，再往下运行
  while (1) {
    XNextEvent(dpy, &ev);
    if (ev.type == MapNotify) {
      break;
    }
  }

  XNextEvent(dpy, &ev);

  //销毁窗口
  XDestroyWindow(dpy, win);
  //关闭连接
  XCloseDisplay(dpy);
  return 0;
}
