#ifndef __FRONTIER_ENGINE_X11_H_
#define __FRONTIER_ENGINE_X11_H_

#include <frontier/engine.h>

#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/extensions/XShm.h>

namespace Frontier
{

#define MWM_HINTS_DECORATIONS   (1L << 1)

#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)

typedef struct
{
    long flags;
    long functions;
    long decorations;
    long input_mode;
    long state;
} MotifWmHints;

class X11FrontierWindow : public Frontier::FrontierEngineWindow
{
 private:
    Window m_x11Window;
    GC m_gc;
    XImage* m_xImage;
    char* m_xImageData;
    Frontier::Size m_size;

    XShmSegmentInfo m_shminfo;

 public:
    X11FrontierWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~X11FrontierWindow();

    virtual bool init();
    virtual void show();
    virtual void hide();
    virtual bool update();

    virtual void setPosition(unsigned int x, unsigned int y);

    virtual void requestUpdate();

    Window getX11Window() { return m_x11Window; }
};

class X11Engine : public Frontier::FrontierEngine
{
 private:
    Display* m_display;
    bool m_useShm;
    XVisualInfo m_visualInfo;

    std::vector<X11FrontierWindow*> m_engineWindows;

    Atom WM_DELETE_WINDOW;

 public:
    X11Engine(Frontier::FrontierApp* app);
    virtual ~X11Engine();

    bool init();
    bool initWindow(Frontier::FrontierWindow* window);

    X11FrontierWindow* getWindow(Window window);

    virtual bool checkEvents();

    Atom* getWMDeleteWindow() { return &WM_DELETE_WINDOW; }
    Display* getDisplay() { return m_display; }
    bool useShm() { return m_useShm; }
    XVisualInfo* getVisualInfo() { return &m_visualInfo; }
};

}

#endif
