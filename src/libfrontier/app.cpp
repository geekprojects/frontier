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
#include <frontier/contextmenu.h>
#include <sys/time.h>

#include <typeinfo>

#ifdef FRONTIER_ENGINE_SDL
#   include "engines/sdl/sdl_engine.h"
#elif FRONTIER_ENGINE_COCOA
#   include "engines/cocoa/CocoaEngine.h"
#else
#   error No engine defined
#endif

#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x

using namespace std;
using namespace Frontier;

FrontierApp::FrontierApp(wstring name) : Logger(L"FrontierApp[" + name + L"]")
{
    m_activeWindow = NULL;
    m_contextMenuWindow = NULL;
    m_name = name;

    m_engine = NULL;
    m_theme = NULL;
    m_fontManager = NULL;

    m_appMenu = NULL;
}

FrontierApp::~FrontierApp()
{
    for (FrontierWindow* window : m_windows)
    {
        delete window;
    }
    m_windows.clear();

    gc();

    for (FrontierObject* obj : m_objects)
    {
        log(Geek::DEBUG, "~FrontierApp: Leaked object %p: type=%s references=%d", obj, typeid(*obj).name(), obj->getRefCount());
    }

    if (m_theme != NULL)
    {
        delete m_theme;
    }

    if (m_fontManager != NULL)
    {
        delete m_fontManager;
    }

    if (m_engine != NULL)
    {
        delete m_engine;
    }
}

void FrontierApp::setEngine(FrontierEngine* engine)
{
    if (m_engine != NULL)
    {
        log(Geek::ERROR, "setEngine: Cannot change engine!");
    }
    m_engine = engine;
}

bool FrontierApp::init()
{
    bool res;

    // A custom app can set their own engine
    if (m_engine == NULL)
    {
#ifdef FRONTIER_ENGINE_SDL
        m_engine = new FrontierEngineSDL(this);
#elif FRONTIER_ENGINE_COCOA
        m_engine = new CocoaEngine(this);
#else
#error No engine defined
#endif
    }

    res = m_engine->init();
    if (!res)
    {
return false;
    }

    m_fontManager = new FontManager();
    res = m_fontManager->init();
    if (!res)
    {
        return false;
    }

#if defined(__APPLE__) && defined(__MACH__)
    m_fontManager->scan("/Library/Fonts");
    m_fontManager->scan("/System/Library/Fonts");
    const char* homechar = getenv("HOME");
    m_fontManager->scan(string(homechar) + "/Library/Fonts");
#else
    m_fontManager->scan("/usr/share/fonts");
#endif

#ifdef FONTSDIR
    m_fontManager->scan(STRINGIFY(FONTSDIR));
#endif

    m_fontManager->scan("fonts");

    m_theme = new UITheme(this);
    res = m_theme->init();
    if (!res)
    {
        return false;
    }

    return true;
}

void FrontierApp::registerObject(FrontierObject* obj)
{
    m_objects.insert(obj);
}

void FrontierApp::gc()
{
    unsigned int totalFreed = 0;
    unsigned int freed = 0;
    do
    {
        set<FrontierObject*> objects = m_objects; // Make a copy!
        freed = 0;
        for (FrontierObject* obj : objects)
        {
            //log(DEBUG, "gc: %p: references=%d", obj, obj->getRefCount());
            int count = obj->getRefCount();
            if (count <= 0)
            {
                //log(DEBUG, "gc: %p: references=%d", obj, obj->getRefCount());
                if (count < 0)
                {
                    log(Geek::WARN, "gc: %p: Reference Count is less than zero??", obj);
                }
                delete obj;
                m_objects.erase(obj);
                freed++;
            }
        }
        totalFreed += freed;
    }
    while (freed > 0);

    if (totalFreed > 0)
    {
        log(Geek::DEBUG, "gc: totalFreed=%u, currentCount=%lu", totalFreed, m_objects.size());
    }
}

ContextMenu* FrontierApp::getContextMenuWindow()
{
    if (m_contextMenuWindow == NULL)
    {
        m_contextMenuWindow = new ContextMenu(this);
    }
    return m_contextMenuWindow;
}

string FrontierApp::getConfigDir()
{
    return m_engine->getConfigDir();
}

void FrontierApp::addWindow(FrontierWindow* window)
{
    m_windows.push_back(window);
}

void FrontierApp::setActiveWindow(FrontierWindow* window)
{
    if (window == m_activeWindow)
    {
        return;
    }

    if (m_activeWindow != NULL)
    {
        m_activeWindow->lostFocus();
    }

    m_activeWindow = window;
    if (m_activeWindow != NULL)
    {
        m_activeWindow->gainedFocus();
    }

    m_activeWindowChangedSignal.emit(m_activeWindow);
}

FrontierWindow* FrontierApp::getActiveWindow()
{
    return m_activeWindow;
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
}

void FrontierApp::update()
{
    for (FrontierWindow* window : m_windows)
    {
        if (window->getContent() != NULL && window->getContent()->isDirty())
        {
            window->update();
        }
    }

    gc();
}

void FrontierApp::postEvent(Event* event)
{
    handleEvent(event);
}

void FrontierApp::handleEvent(Event* event)
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

string FrontierApp::chooseFile(int flags, string path, string pattern)
{
    return m_engine->chooseFile(flags, path, pattern);
}

uint64_t FrontierApp::getTimestamp() const
{
    timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t millis;
    millis = tv.tv_sec * 1000l;
    millis += tv.tv_usec / 1000l;

    return millis;
}

