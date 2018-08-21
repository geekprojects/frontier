
#include "cocoa_engine.h"

CocoaEngine::CocoaEngine(FrontierApp* app) : FrontierEngine(app)
{
}

CocoaEngine::~CocoaEngine()
{
}

bool CocoaEngine::init()
{
    bool res;

    res = createApplication();
    if (!res)
    {
return false;
    }

    return true;
}

bool CocoaEngine::initWindow(FrontierWindow* window)
{

    bool res;

    CocoaWindow* cw = new CocoaWindow(window);

    res = cw->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(cw);
    return true;
}

bool CocoaEngine::checkEvents()
{
    run();

    return true;
}

