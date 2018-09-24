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

#ifndef __FRONTIER_UI_H_
#define __FRONTIER_UI_H_

#include <vector>

#include <geek/gfx-surface.h>

#include <frontier/utils.h>
#include <frontier/fonts.h>
#include <frontier/messages.h>
#include <frontier/theme.h>

#include <sigc++/sigc++.h>

namespace Frontier
{
class FrontierEngine;
class FrontierApp;
class Widget;
class UITheme;

class FrontierEngineWindow;

enum MessageBoxType
{
    MESSAGE_INFO,
    MESSAGE_ALERT,
};

class FrontierApp
{
 private:
    FrontierEngine* m_engine;

    FontManager* m_fontManager;
    UITheme* m_theme;

 public:
    FrontierApp();
    virtual ~FrontierApp();

    FrontierEngine* getEngine() { return m_engine; }
    FontManager* getFontManager() { return m_fontManager; }
    UITheme* getTheme() { return m_theme; }

    virtual bool init();
    virtual bool main();

    void postMessage(Frontier::Message* message);
    virtual void handleMessage(Frontier::Message* message);

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile();
};

class FrontierWindow
{
 private:
    FrontierEngineWindow* m_engineWindow;
    bool m_initialised;

    FrontierApp* m_app;

    Frontier::Size m_size;

    Widget* m_widget;
    Widget* m_activeWidget;
    Widget* m_mouseOverWidget;
    Widget* m_dragWidget;

    Geek::Gfx::Surface* m_surface;

    sigc::signal<bool> m_closeSignal;

    bool initInternal();

 protected:
    virtual bool init();

 public:
    FrontierWindow(FrontierApp* app);
    ~FrontierWindow();

    void setContent(Widget* widget);
    void setActiveWidget(Widget* widget) { m_activeWidget = widget; }
    void setDragWidget(Widget* widget) { m_dragWidget = widget; }

    void show();
    void update();

    void setEngineWindow(FrontierEngineWindow* few) { m_engineWindow = few; }
    FrontierEngineWindow* getEngineWindow() { return m_engineWindow; }
    FrontierApp* getApp() { return m_app; }

    void setSize(Frontier::Size size);
    Frontier::Size getSize() { return m_size; }
    Geek::Gfx::Surface* getSurface() { return m_surface; }

    void postMessage(Frontier::Message* message);
    virtual bool handleMessage(Frontier::Message* message);
    sigc::signal<bool> closeSignal() { return m_closeSignal; }
};

};

#endif
