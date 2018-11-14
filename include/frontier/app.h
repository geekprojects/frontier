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

#ifndef __FRONTIER_APP_H_
#define __FRONTIER_APP_H_

#include <vector>
#include <set>

#include <geek/gfx-surface.h>

#include <frontier/object.h>
#include <frontier/utils.h>
#include <frontier/fonts.h>
#include <frontier/messages.h>
#include <frontier/theme.h>
#include <frontier/menu.h>

#include <sigc++/sigc++.h>

namespace Frontier
{
class FrontierEngine;
class FrontierApp;
class Widget;
class UITheme;
class ContextMenu;

class FrontierEngineWindow;

enum MessageBoxType
{
    MESSAGE_INFO,
    MESSAGE_ALERT,
};

class FrontierApp
{
 private:
    std::wstring m_name;
    FrontierEngine* m_engine;

    std::set<FrontierObject*> m_objects;

    FontManager* m_fontManager;
    UITheme* m_theme;

    ContextMenu* m_contextMenuWindow;

    std::vector<MenuItem*> m_appMenu;

    std::vector<FrontierWindow*> m_windows;
    FrontierWindow* m_activeWindow;

 public:
    FrontierApp(std::wstring name);
    virtual ~FrontierApp();

    std::wstring getName() { return m_name; }

    void registerObject(FrontierObject* object);
    void gc();

    FrontierEngine* getEngine() { return m_engine; }
    FontManager* getFontManager() const { return m_fontManager; }
    UITheme* getTheme() const { return m_theme; }

    ContextMenu* getContextMenuWindow();

    std::string getConfigDir();

    std::vector<MenuItem*>* getAppMenu() { return &m_appMenu; }

    void addWindow(FrontierWindow* window);
    void setActiveWindow(FrontierWindow* activeWindow);
    FrontierWindow* getActiveWindow();

    virtual bool init();
    virtual bool main();

    void update();

    void postMessage(Frontier::Message* message);
    virtual void handleMessage(Frontier::Message* message);

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile();

    uint64_t getTimestamp() const;
};

};

#endif
