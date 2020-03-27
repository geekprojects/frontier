
#include <frontier/engines/windowing.h>

using namespace Frontier;
using namespace std;

WindowingEngine::WindowingEngine(FrontierApp* app) : EmbeddedEngine(app)
{
}

WindowingEngine::~WindowingEngine()
{
}


void WindowingEngine::showWindow(FrontierWindow* window)
{
    hideWindow(window);

    m_windowOrder.push_front(window);

}

void WindowingEngine::hideWindow(FrontierWindow* window)
{
    for (auto it = m_windowOrder.begin(); it != m_windowOrder.end(); it++)
    {
        if (*it == window)
        {
            m_windowOrder.erase(it);
            break;
        }
    }
}

FrontierWindow* WindowingEngine::windowAt(int x, int y)
{
    for (auto w : m_windowOrder)
    {
        if (w->getRect().intersects(x, y))
        {
            return w;
        }
    }
    return NULL;
}


void WindowingEngine::mouseMotion(int x, int y)
{
    FrontierWindow* window = windowAt(x, y);
    if (window != NULL)
    {
        MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
        mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
        mouseMotionEvent->x = x - window->getPosition().x;
        mouseMotionEvent->y = y - window->getPosition().y;
        window->handleEvent(mouseMotionEvent);
    }
}

void WindowingEngine::mouseButton(int x, int y, int button, bool direction)
{
    FrontierWindow* window = windowAt(x, y);
    if (window != NULL)
    {
        // Bring it to the front
        showWindow(window);

        MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
        mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
        mouseButtonEvent->direction = direction;
        mouseButtonEvent->buttons = button;
        mouseButtonEvent->x = x - window->getPosition().x;
        mouseButtonEvent->y = y - window->getPosition().y;
        window->handleEvent(mouseButtonEvent);
    }
}


