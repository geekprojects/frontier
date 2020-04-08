
#include <frontier/engines/windowing.h>

using namespace Frontier;
using namespace Geek;

WindowingEngineWindow::WindowingEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window)
    : EmbeddedWindow(engine, window)
{
}

WindowingEngineWindow::~WindowingEngineWindow()
{
}

bool WindowingEngineWindow::init()
{
    Size windowSize = getWindow()->getSize();
    Size screenSize = ((WindowingEngine*)getEngine())->getScreenSize();
    log(DEBUG, "init: windowSize=%d, %d", windowSize.width, windowSize.height);
    log(DEBUG, "init: screenSize=%d, %d", screenSize.width, screenSize.height);

    if (getWindow()->isFullScreen())
    {
        getWindow()->setSize(screenSize);
    }

    return true;
}

void WindowingEngineWindow::show()
{
    Size windowSize = getWindow()->getSize();
    Size screenSize = ((WindowingEngine*)getEngine())->getScreenSize();
    log(DEBUG, "show: windowSize=%d, %d", windowSize.width, windowSize.height);
    log(DEBUG, "show: screenSize=%d, %d", screenSize.width, screenSize.height);

    ((WindowingEngine*)getEngine())->showWindow(getWindow());
}

void WindowingEngineWindow::hide()
{
    ((WindowingEngine*)getEngine())->hideWindow(getWindow());
}


