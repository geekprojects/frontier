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
    explicit CocoaEngine(FrontierApp* app);
    ~CocoaEngine() override;

    bool init() override;

    bool initWindow(FrontierWindow* window) override;

    bool checkEvents() override;

    bool quit(bool) override;

    std::string getConfigDir() override;

    void message(std::string title, std::string message) override;
    bool confirmBox(std::string title, std::string message) override;
    std::string chooseFile(int flags, std::string path, std::string pattern) override;
    ColourPickerWindow* openColourPickerWindow(Geek::Gfx::Colour colour) override;

    bool providesMenus() override { return true; }

    void updateMenu(FrontierWindow* window);

    void* getApplication() { return m_application; }
};

class CocoaColourPickerWindow : public ColourPickerWindow
{
 private:

 public:
    explicit CocoaColourPickerWindow(Geek::Gfx::Colour colour);
    ~CocoaColourPickerWindow() override;
};

}

#endif

