
#include <frontier/engines/embedded.h>

using namespace std;
using namespace Frontier;

EmbeddedEngine::EmbeddedEngine(FrontierApp* app) : FrontierEngine(app)
{
    m_scaleFactor = 1.0;
}

EmbeddedEngine::~EmbeddedEngine()
{
}

bool EmbeddedEngine::init()
{
    return true;
}

bool EmbeddedEngine::initWindow(FrontierWindow* window)
{
    EmbeddedWindow* ew = new EmbeddedWindow(this, window);
    ew->init();
    window->setEngineWindow(ew);

    return true;
}

bool EmbeddedEngine::checkEvents()
{
    return true;
}


std::string EmbeddedEngine::getConfigDir()
{
    return string("/tmp");
}


void EmbeddedEngine::message(std::string title, std::string message)
{
}

bool EmbeddedEngine::confirmBox(std::string title, std::string message)
{
    return true;
}

std::string EmbeddedEngine::chooseFile(int flags, std::string path, std::string pattern)
{
    return string("/tmp/test.txt");
}

