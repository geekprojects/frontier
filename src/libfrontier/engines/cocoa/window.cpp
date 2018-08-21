
#include "cocoa_engine.h"

using namespace std;
using namespace Frontier;

CocoaWindow::CocoaWindow(FrontierWindow* window) : FrontierEngineWindow(window)
{
}

CocoaWindow::~CocoaWindow()
{
}


bool CocoaWindow::init()
{
    return createCocoaWindow();
}

bool CocoaWindow::show()
{
    return true;
}

bool CocoaWindow::update()
{
    Size winSize = m_window->getSize();
    //setSize(winSize);

#if 1
    Size currentSize = getSize();
    if (currentSize.width != winSize.width || currentSize.height != winSize.height)
    {
        setSize(winSize);
    }
#endif

    drawSurface(m_window->getSurface());

    return true;
}

