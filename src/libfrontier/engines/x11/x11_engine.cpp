
#include "x11_engine.h"

using namespace std;
using namespace Frontier;
using namespace Geek;

X11Engine::X11Engine(FrontierApp* app) : FrontierEngine(app)
{
}

X11Engine::~X11Engine()
{
}

bool X11Engine::init()
{
    m_display = XOpenDisplay(NULL);
    if (m_display == NULL)
    {
        log(ERROR, "Failed to open display");
        return false;
    }

    int ignore;
    int res;
    res = XQueryExtension(m_display, "MIT-SHM", &ignore, &ignore, &ignore);
    if (res)
    {
        m_useShm = true;
    }
    else
    {
        m_useShm = false;
    }

    res = XMatchVisualInfo(m_display, XDefaultScreen(m_display), 24, TrueColor, &m_visualInfo);
    if (!res)
    {
        log(ERROR, "Failed to find appropriate visual!");
        return false;
    }

    const char *vic_name[] = {
        "StaticGray", "GrayScale", "StaticColor",
        "PseudoColor", "TrueColor", "DirectColor"
    };
    printf("Using visual= %ld, class=%s, depth=%d\n",
        m_visualInfo.visualid,
        vic_name[m_visualInfo.c_class],
        m_visualInfo.depth); 

    WM_DELETE_WINDOW = XInternAtom(m_display, "WM_DELETE_WINDOW", False);

    return true;
}

bool X11Engine::initWindow(Frontier::FrontierWindow* window)
{
    bool res;

    X11FrontierWindow* few = new X11FrontierWindow(this, window);

    res = few->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(few);

    m_engineWindows.push_back(few);

    return true;
}

X11FrontierWindow* X11Engine::getWindow(Window window)
{
    for (X11FrontierWindow* engineWindow : m_engineWindows)
    {
        if (engineWindow->getX11Window() == window)
        {
            return engineWindow;
        }
    }
    return NULL;
}

bool X11Engine::checkEvents()
{
    XEvent event;
    XNextEvent(m_display, &event);

    switch (event.type)
    {
        case ButtonRelease:
        case ButtonPress:
        {
            X11FrontierWindow* few = getWindow(event.xbutton.window);
            if (few == NULL)
            {
                return true;
            }
            MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
            mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;

            mouseButtonEvent->x = event.xbutton.x;
            mouseButtonEvent->y = event.xbutton.y;
            //mouseButtonEvent->modifier = translateModifier(event.xbutton.state);
            //mouseButtonEvent->button = event.xbutton.button;
            mouseButtonEvent->direction = (event.type == ButtonPress);
            few->getWindow()->handleEvent(mouseButtonEvent);
        } break;

        case MotionNotify:
        {
            X11FrontierWindow* few = getWindow(event.xmotion.window);
            if (few == NULL)
            {
                return true;
            }

            MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
            mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
            mouseMotionEvent->x = event.xbutton.x;
            mouseMotionEvent->y = event.xbutton.y;

            few->getWindow()->handleEvent(mouseMotionEvent);
        } break;

        case Expose:
        {
            X11FrontierWindow* window = getWindow(event.xexpose.window);
            window->getWindow()->update(true);
        } break;

        case ClientMessage:
        {
            X11FrontierWindow* few = getWindow(event.xclient.window);
            if (few == NULL)
            {
                return true;
            }
            unsigned int type = static_cast<unsigned int>(event.xclient.data.l[0]);
            log(DEBUG, "checkEvents: checkEvents: window=%p, type=%d", few, type);
            if (type == WM_DELETE_WINDOW)
            {
                log(DEBUG, "checkEvents: checkEvents: Delete Window!");
                few->getWindow()->closeSignal().emit();
            }
        } break;
    }
    return true;
}


