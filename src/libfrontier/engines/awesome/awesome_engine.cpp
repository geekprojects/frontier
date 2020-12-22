
#include "awesome.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <cstdio>
#include <unistd.h>

using namespace Frontier;
using namespace Geek;
using namespace Awesome;
using namespace std;

FRONTIER_ENGINE(Awesome, Frontier::AwesomeEngine)

AwesomeEngine::AwesomeEngine(FrontierApp* app) : FrontierEngine(app)
{
    //m_messageSignal = Thread::createCondVar();
}

AwesomeEngine::~AwesomeEngine()
{
    delete m_connection;
}

bool AwesomeEngine::init()
{
    log(DEBUG, "init: Here!");

    m_connection = new ClientConnection("unix:/usr/local/var/awesome/ads.socket");
    //m_connection = new ClientConnection("inet:localhost:16523");

    bool res;
    res = m_connection->connect();
    if (!res)
    {
        log(DEBUG, "init: Failed to connect");
        return false;
    }

    log(DEBUG, "init: Getting info...");
    InfoResponse* info = m_connection->getInfo();
    log(DEBUG, "init: name=%s, vendor=%s", info->name, info->vendor);
    log(DEBUG, "init-test: numDisplays=%d", info->numDisplays);

    InfoDisplayRequest infoDisplayRequest;
    infoDisplayRequest.display = 0;
    InfoDisplayResponse* response = static_cast<InfoDisplayResponse*>(m_connection->send(
        &infoDisplayRequest,
        sizeof(infoDisplayRequest)));
    m_scale = response->scale;
    delete response;
    delete info;

    log(DEBUG, "init: Done!");
    return true;
}

bool AwesomeEngine::checkEvents()
{
    Awesome::Event* event = m_connection->eventWait();
    if (event == nullptr)
    {
        return false;
    }

    AwesomeWindow* awesomeWindow = nullptr;
    if (event->windowId > 0)
    {
        auto it = m_windows.find(event->windowId);
        if (it != m_windows.end())
        {
            awesomeWindow = it->second;
        }
    }
    //log(DEBUG, "checkEvents: Got event! type=0x%x, window=%d (%p)", event->eventType, event->windowId, awesomeWindow);
    switch (event->eventType)
    {
        case Awesome::AWESOME_EVENT_MOUSE_BUTTON:
        {
            if (awesomeWindow != nullptr)
            {
                MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
                mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
                mouseButtonEvent->window = awesomeWindow->getWindow();
                mouseButtonEvent->x = event->mouse.x;
                mouseButtonEvent->y = event->mouse.y;
                mouseButtonEvent->buttons = event->mouse.button.buttons;
                mouseButtonEvent->direction = event->mouse.button.direction;
                mouseButtonEvent->doubleClick = false;
                /*
                log(
                    DEBUG, "checkEvents: Sending mouse button event: x=%d, y=%d, buttons=%d, direction=%d",
                    mouseButtonEvent->x,
                    mouseButtonEvent->y,
                    mouseButtonEvent->buttons,
                    mouseButtonEvent->direction);
                    */
                awesomeWindow->getWindow()->handleEvent(mouseButtonEvent);
            }
        } break;

        case Awesome::AWESOME_EVENT_MOUSE_MOTION:
        {
            if (awesomeWindow != nullptr)
            {
                MouseMotionEvent* mouseButtonEvent = new MouseMotionEvent();
                mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
                mouseButtonEvent->window = awesomeWindow->getWindow();
                mouseButtonEvent->x = event->mouse.x;
                mouseButtonEvent->y = event->mouse.y;
                /*
                log(
                    DEBUG, "checkEvents: Sending mouse motion event: x=%d, y=%d",
                    mouseButtonEvent->x,
                    mouseButtonEvent->y);
                    */
                awesomeWindow->getWindow()->handleEvent(mouseButtonEvent);
            }
        } break;
        default:
            log(DEBUG, "checkEvents: Unhandled event: 0x%x", event->eventType);
    }

    return true;
}

bool AwesomeEngine::initWindow(FrontierWindow* window)
{
    AwesomeWindow* clientWindow = new AwesomeWindow(this, window);
    bool res;
    res = clientWindow->init();
    if (!res)
    {
        return false;
    }

    int id = clientWindow->getWindowId();
    log(DEBUG, "initWindow: id=%d", id);
    m_windows.insert(make_pair(id, clientWindow));

    window->setEngineWindow(clientWindow);
    return true;
}
