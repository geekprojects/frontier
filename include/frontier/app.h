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
#include <geek/core-logger.h>
#include <geek/fonts.h>

#include <frontier/object.h>
#include <frontier/utils.h>
#include <frontier/events.h>
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
class DatePickerWindow;

class FrontierEngineWindow;

enum MessageBoxType
{
    MESSAGE_INFO,
    MESSAGE_ALERT,
};

enum ChooseFileFlags
{
    DIRECTORIES_ONLY = 0x1
};

class FrontierApp : public Geek::Logger
{
 private:
    std::wstring m_name;
    FrontierEngine* m_engine;

    std::set<FrontierObject*> m_objects;

    Geek::FontManager* m_fontManager;
    UITheme* m_theme;

    Menu* m_appMenu;
    ContextMenu* m_contextMenuWindow;

    std::vector<FrontierWindow*> m_windows;
    FrontierWindow* m_activeWindow;

    sigc::signal<void, FrontierWindow*> m_activeWindowChangedSignal;

    DatePickerWindow* m_datePickerWindow;

 protected:
    void setEngine(FrontierEngine* m_engine);
    std::vector<FrontierWindow*>& getWindows() { return m_windows; }

 public:
    FrontierApp(std::wstring name);
    virtual ~FrontierApp();

    std::wstring getName() { return m_name; }

    void registerObject(FrontierObject* object);
    void gc();
    unsigned int getObjectCount() { return m_objects.size(); }

    FrontierEngine* getEngine() { return m_engine; }
    Geek::FontManager* getFontManager() const { return m_fontManager; }
    UITheme* getTheme() const { return m_theme; }

    ContextMenu* getContextMenuWindow();

    std::string getConfigDir();

    void setAppMenu(Menu* menu) { m_appMenu = menu; }
    Menu* getAppMenu() { return m_appMenu; }

    void addWindow(FrontierWindow* window);
    void setActiveWindow(FrontierWindow* activeWindow);
    FrontierWindow* getActiveWindow();

    virtual bool init();
    virtual bool main();
    virtual bool quit();

    void update();

    void postEvent(Frontier::Event* event);
    virtual void handleEvent(Frontier::Event* event);

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);

    uint64_t getTimestamp() const;

    void openDatePicker();

    void onAboutMenu(MenuItem* item);
    void onQuitMenu(MenuItem* item);

    virtual sigc::signal<void, FrontierWindow*> activeWindowChangedSignal() { return m_activeWindowChangedSignal; }
};

};

#endif
