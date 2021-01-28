#include "frontier/engines/awesome.h"
#include <frontier/widgets.h>

#include <wchar.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;
using namespace Awesome;

AwesomeWindow::AwesomeWindow(FrontierEngine* engine, FrontierWindow* window) : FrontierEngineWindow(engine, window)
{

}
AwesomeWindow::~AwesomeWindow()
{

}

bool AwesomeWindow::init()
{
    m_currentSize = m_window->getSize();
    log(DEBUG, "init: size=%d, %d", m_currentSize.width, m_currentSize.height);

    m_windowId = 0;

    ClientConnection* connection = ((AwesomeEngine*)m_engine)->getConnection();

    WindowCreateRequest createWindowRequest;
    createWindowRequest.x = WINDOW_POSITION_ANY;
    createWindowRequest.y = WINDOW_POSITION_ANY;
    createWindowRequest.width = m_currentSize.width;
    createWindowRequest.height = m_currentSize.height;
    createWindowRequest.flags = Awesome::WINDOW_MOTION_EVENTS;
    if (m_window->hasBorder())
    {
        createWindowRequest.flags |= Awesome::WINDOW_BORDER | Awesome::WINDOW_TITLE;
    }

    memcpy(createWindowRequest.title, m_window->getTitle().c_str(), m_window->getTitle().size());

    log(DEBUG, "init: Creating window...");
    WindowCreateResponse* windowCreateResponse = static_cast<WindowCreateResponse*>(connection->send(&createWindowRequest, sizeof(createWindowRequest)));

    log(DEBUG, "init: window id=%d", windowCreateResponse->windowId);
    m_windowId = windowCreateResponse->windowId;

    delete windowCreateResponse;

    m_scale = ((AwesomeEngine*)m_engine)->getScale();

    return true;
}

bool AwesomeWindow::update()
{
    Size size = m_window->getSize();
    Surface* surface = m_window->getSurface();
    int bytes = surface->getDataLength();
    ClientConnection* connection = ((AwesomeEngine*)m_engine)->getConnection();
    if (m_sharedMemory == nullptr || m_sharedMemory->getSize() < bytes)
    {
        if (m_sharedMemory != nullptr)
        {
            connection->destroySharedMemory(m_sharedMemory);
        }
        log(DEBUG, "update: Creating shared memory buffer...");
        m_sharedMemory = connection->createSharedMemory(bytes);
        log(DEBUG, "update: Got shared memory buffer");
        if (m_sharedMemory == nullptr)
        {
            return false;
        }
    }

    if (size != m_currentSize)
    {
        WindowSetSizeRequest setSizeRequest;
        setSizeRequest.windowId = m_windowId;
        setSizeRequest.width = size.width;
        setSizeRequest.height = size.height;
        log(DEBUG, "update: Sending set size request...");
        connection->send(&setSizeRequest, sizeof(setSizeRequest));
        log(DEBUG, "update: Sending set size request response!");
        m_currentSize = size;
    }

    memcpy(m_sharedMemory->getAddr(), surface->getData(), bytes);

    WindowUpdateRequest windowUpdateRequest;
    windowUpdateRequest.windowId = m_windowId;
    windowUpdateRequest.width = surface->getWidth();
    windowUpdateRequest.height = surface->getHeight();
    strncpy(windowUpdateRequest.shmPath, m_sharedMemory->getPath().c_str(), 256);
    //log(DEBUG, "update: Sending update request...");
    connection->send(&windowUpdateRequest, sizeof(windowUpdateRequest));
    //log(DEBUG, "update: Got update request response!");

    return true;
}

void AwesomeWindow::requestUpdate()
{
    update();
}

void AwesomeWindow::show()
{
    WindowSetVisibleRequest windowSetVisibleRequest;
    windowSetVisibleRequest.windowId = m_windowId;
    windowSetVisibleRequest.visible = true;

    ClientConnection* connection = ((AwesomeEngine*)m_engine)->getConnection();
    connection->send(&windowSetVisibleRequest, sizeof(windowSetVisibleRequest));
}

void AwesomeWindow::hide()
{
    WindowSetVisibleRequest windowSetVisibleRequest;
    windowSetVisibleRequest.windowId = m_windowId;
    windowSetVisibleRequest.visible = false;

    ClientConnection* connection = ((AwesomeEngine*)m_engine)->getConnection();
    connection->send(&windowSetVisibleRequest, sizeof(windowSetVisibleRequest));
}

