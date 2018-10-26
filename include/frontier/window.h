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

#ifndef __FRONTIER_WINDOW_H_
#define __FRONTIER_WINDOW_H_

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

class FrontierEngineWindow;

enum WindowFlags
{
    WINDOW_BORDER = 1,
    WINDOW_RESIZEABLE = 2,

    WINDOW_NORMAL = WINDOW_BORDER | WINDOW_RESIZEABLE,
    WINDOW_POPUP = 0
};

class FrontierWindow
{
 private:
    FrontierEngineWindow* m_engineWindow;
    bool m_initialised;

    FrontierApp* m_app;

    std::wstring m_title;
    int m_flags;
    //bool m_isMain;
    Frontier::Size m_size;

    Widget* m_widget;
    Widget* m_activeWidget;
    Widget* m_mouseOverWidget;
    Widget* m_dragWidget;
    uint64_t m_dragTime;

    Geek::Gfx::Surface* m_surface;

    sigc::signal<bool> m_closeSignal;

    bool initInternal();

 protected:
    virtual bool init();

 public:
    FrontierWindow(FrontierApp* app, std::wstring title, int flags);
    ~FrontierWindow();

    std::wstring getTitle() { return m_title; }
    bool hasBorder() { return !!(m_flags & WINDOW_BORDER); }
    bool isResizeable() { return !!(m_flags & WINDOW_RESIZEABLE); }

    void setPosition(Geek::Vector2D position);

    void setContent(Widget* widget);
    Widget* getContent() { return m_widget; }
    void setActiveWidget(Widget* widget) { m_activeWidget = widget; }
    Widget* getActiveWidget() { return m_activeWidget; }
    void setDragWidget(Widget* widget);

    void show();
    void hide();
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

    Geek::Vector2D getScreenPosition(Geek::Vector2D windowPos);

};

};

#endif
