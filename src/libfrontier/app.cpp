/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <frontier/frontier.h>
#include <frontier/config.h>

#ifdef FRONTIER_ENGINE_SDL
#   include "engines/sdl/sdl_engine.h"
#elif FRONTIER_ENGINE_COCOA
#   include "engines/cocoa/cocoa_engine.h"
#else
#   error No engine defined
#endif

using namespace std;
using namespace Frontier;

FrontierApp::FrontierApp()
{
}

FrontierApp::~FrontierApp()
{
}

bool FrontierApp::init()
{
    bool res;

#ifdef FRONTIER_ENGINE_SDL
    m_engine = new FrontierEngineSDL(this);
#elif FRONTIER_ENGINE_COCOA
    m_engine = new CocoaEngine(this);
#else
#error No engine defined
#endif

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

    m_fontManager->scan("/System/Library/Fonts");
    m_fontManager->scan("/Users/ian/Library/Fonts");
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

void FrontierApp::message(string title, string message)
{
    m_engine->message(title, message);
}

bool FrontierApp::confirmBox(string title, string message)
{
    return m_engine->confirmBox(title, message);
}

string FrontierApp::chooseFile()
{
    return m_engine->chooseFile();
}

