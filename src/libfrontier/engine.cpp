
#include <frontier/engine.h>

FrontierEngine::FrontierEngine(FrontierApp* app) : Geek::Logger("FrontierEngine")
{
    m_app = app;
}

FrontierEngine::~FrontierEngine()
{
}

bool FrontierEngine::init()
{
    return true;
}

bool FrontierEngine::initWindow(FrontierWindow* window)
{
    return true;
}

bool FrontierEngine::checkEvents()
{
    // Just quit
    return false;
}

FrontierEngineWindow::FrontierEngineWindow(FrontierWindow* window)
{
     m_window = window;
}

FrontierEngineWindow::~FrontierEngineWindow()
{
}

bool FrontierEngineWindow::init()
{
    return true;
}

bool FrontierEngineWindow::show()
{
    return true;
}

bool FrontierEngineWindow::update()
{
    return true;
}

