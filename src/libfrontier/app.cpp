
#include <frontier/frontier.h>

#include "engines/sdl/sdl_engine.h"

using namespace std;

FrontierApp::FrontierApp()
{
}

FrontierApp::~FrontierApp()
{
}

bool FrontierApp::init()
{
    bool res;

    m_engine = new FrontierEngineSDL(this);
    res = m_engine->init();
    if (!res)
    {
return false;
    }

    m_fontManager = new FontManager("/Library/Fonts");
    res = m_fontManager->init();
    if (!res)
    {
        return false;
    }

    m_fontManager->scan("fonts");

    m_theme = new UITheme(this);
    res = m_theme->init();
    if (!res)
    {
        return false;
    }

    return true;
}

bool FrontierApp::main()
{
    while (true)
    {
        bool res;
        res = m_engine->checkEvents();
        if (!res)
        {
            return false;
        }
    }

    return true;
}

void FrontierApp::postMessage(Message* message)
{
    handleMessage(message);
}

void FrontierApp::handleMessage(Message* message)
{
}


