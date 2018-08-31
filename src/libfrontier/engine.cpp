
#include <frontier/engine.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

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

string FrontierEngine::chooseFile()
{
    log(WARN, "chooseFile not implemented");
    return "";
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

float FrontierEngineWindow::getScaleFactor()
{
    return 1.0;
}

