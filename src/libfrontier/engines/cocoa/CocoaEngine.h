/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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

#ifndef __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_
#define __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_

#include <frontier/engine.h>
#include <frontier/windows/colourpicker.h>

namespace Frontier {

class CocoaEngine : public FrontierEngine
{
 private:
    void* m_application;
    void* m_appDelegate;
    void* m_windowMenu;

    Menu* m_currentMenu;

    bool createApplication();
    bool run();

    void updateMenu(Menu* menu);
    void addAppMenu(void* menu);

    void onActiveWindowChanged(FrontierWindow* window);

 public:
    CocoaEngine(FrontierApp* app);
    virtual ~CocoaEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual bool quit(bool force = false);

    virtual std::string getConfigDir();

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);
    virtual ColourPickerWindow* openColourPickerWindow(Geek::Gfx::Colour colour);

    bool providesMenus() { return true; }

    void updateMenu(FrontierWindow* window);

    void* getApplication() { return m_application; }
};

class CocoaColourPickerWindow : public ColourPickerWindow
{
 private:

 public:
    CocoaColourPickerWindow(Geek::Gfx::Colour colour);
    virtual ~CocoaColourPickerWindow();
};

}

#endif

