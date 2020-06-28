/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
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
#include <geek/gfx-colour.h>
#include <geek/core-logger.h>
#include <geek/core-timers.h>
#include <geek/fonts.h>

#include <frontier/object.h>
#include <frontier/utils.h>
#include <frontier/events.h>
#include <frontier/styles.h>
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
class ColourPickerWindow;

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

/**
 * \brief Main class that represents the application
 *
 * Applications should extend this class to implement their applications, or
 * at least the UI side of it.
 *
 */
class FrontierApp : public Geek::Logger
{
 private:
    std::wstring m_name;
    FrontierEngine* m_engine;

    std::set<FrontierObject*> m_objects;

    Geek::FontManager* m_fontManager;
    UITheme* m_theme;
    StyleEngine* m_styleEngine;
    Geek::Core::TimerManager* m_timerManager;

    Menu* m_appMenu;
    ContextMenu* m_contextMenuWindow;

    std::vector<FrontierWindow*> m_windows;
    FrontierWindow* m_activeWindow;

    sigc::signal<void, FrontierWindow*> m_activeWindowChangedSignal;

 protected:
    /// Override the backend engine. Used to provide embedded engines
    void setEngine(FrontierEngine* m_engine);

    /// Return all windows that have been opened for this App
    std::vector<FrontierWindow*>& getWindows() { return m_windows; }

 public:
    FrontierApp(std::wstring name);
    virtual ~FrontierApp();

    /// Return the name of the application
    std::wstring getName() { return m_name; }

    /// Register object with the Apps garbage collection
    void registerObject(FrontierObject* object);

    /// Perform garbage collection
    void gc();

    /// Return the number of objects that this application is currently tracking
    unsigned int getObjectCount() { return m_objects.size(); }

    /// Get the current back end engine
    FrontierEngine* getEngine() { return m_engine; }

    /// Return the current FontManager
    Geek::FontManager* getFontManager() const { return m_fontManager; }

    /// Return the current theme \deprecared
    UITheme* getTheme() const { return m_theme; }

    /// Return the current StyleEngine
    StyleEngine* getStyleEngine() { return m_styleEngine; }

    /// Return the Timer Manager
    Geek::Core::TimerManager* getTimerManager() { return m_timerManager; }

    /// Get the current ContextMenu
    ContextMenu* getContextMenuWindow();

    /// Return the directory that application specific config should be stored
    std::string getConfigDir();

    /// Set the application-wide menu. This will be the default for all windows
    void setAppMenu(Menu* menu) { m_appMenu = menu; }

    /// Return the application menu
    Menu* getAppMenu() { return m_appMenu; }

    /// Add a new Window
    void addWindow(FrontierWindow* window);

    /// Remove and close a Window
    void removeWindow(FrontierWindow* window);

    /// Activate the specified Window
    void setActiveWindow(FrontierWindow* activeWindow);

    /// Return the currently active Window
    FrontierWindow* getActiveWindow();

    /// Application specific initialisation. Apps should override this
    virtual bool init();

    /// Application main loop. Apps should only override this if really necessary
    virtual bool main();

    /// Request that the app should quit
    virtual bool quit();

    /// Cause all Windows to be updated and redrawn
    void update();

    /// Handle an event from a user
    virtual void handleEvent(Frontier::Event* event);

    /// Create a message box to display a message to the user
    virtual void message(std::string title, std::string message);

    /// Create a box to request the user's confirmation
    virtual bool confirmBox(std::string title, std::string message);

    /// Request a file dialog
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);

    virtual ColourPickerWindow* openColourPickerWindow(Geek::Gfx::Colour colour);

    /// Return the current system timestamp in milliseconds
    uint64_t getTimestamp() const;

    /// Handle requests to the About menu
    virtual void onAboutMenu(MenuItem* item);

    /// Handle requests to the Quit menu
    virtual void onQuitMenu(MenuItem* item);

    /// Signal that fires when the active window changes
    virtual sigc::signal<void, FrontierWindow*> activeWindowChangedSignal() { return m_activeWindowChangedSignal; }
};

};

#endif
