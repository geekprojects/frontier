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
#include <frontier/events.h>
#include <frontier/theme.h>

#include <sigc++/sigc++.h>

namespace Frontier
{
class FrontierEngine;
class FrontierApp;
class Widget;
class Menu;
class MenuList;
class Frame;

class FrontierEngineWindow;

enum WindowFlags
{
    WINDOW_BORDER = 1,
    WINDOW_RESIZEABLE = 2,
    WINDOW_TOOL_TIP = 4,

    WINDOW_NORMAL = WINDOW_BORDER | WINDOW_RESIZEABLE,
};

enum WindowCursor
{
    CURSOR_POINTER,
    CURSOR_EDIT,
    CURSOR_RESIZE_HORIZONTAL,
    CURSOR_RESIZE_VERTICAL,
};

class FrontierWindow : public Geek::Logger
{
 private:
    FrontierEngineWindow* m_engineWindow;
    bool m_initialised;

    FrontierApp* m_app;

    std::wstring m_title;
    int m_flags;
    //bool m_isMain;
    bool m_visible;
    Frontier::Size m_size;

    Frame* m_root;
    Widget* m_content;
    Widget* m_activeWidget;
    Widget* m_mouseOverWidget;
    Widget* m_dragWidget;
    uint64_t m_dragTime;
    Frontier::WindowCursor m_currentCursor;

    Geek::Gfx::Surface* m_surface;

    Menu* m_menu;
    MenuList* m_menuBar;

    sigc::signal<bool> m_closeSignal;
    sigc::signal<bool> m_gainedFocusSignal;
    sigc::signal<bool> m_lostFocusSignal;

    bool initInternal();
    void updateCursor();

 protected:
    virtual bool init();

 public:
    FrontierWindow(FrontierApp* app, std::wstring title, int flags);
    virtual ~FrontierWindow();

    std::wstring getTitle() const { return m_title; }
    bool hasBorder() const { return !!(m_flags & WINDOW_BORDER); }
    bool isResizeable() const { return !!(m_flags & WINDOW_RESIZEABLE); }

    void setPosition(Geek::Vector2D position);
    Geek::Vector2D getPosition();

    void setContent(Widget* widget);
    Widget* getContent() const { return m_content; }
    void setActiveWidget(Widget* widget);
    Widget* getActiveWidget() const { return m_activeWidget; }
    void setDragWidget(Widget* widget);

    void show();
    void hide();
    void update(bool force = false);
    void requestUpdate();

    void setEngineWindow(FrontierEngineWindow* few) { m_engineWindow = few; }
    FrontierEngineWindow* getEngineWindow() { return m_engineWindow; }
    FrontierApp* getApp() const { return m_app; }

    void setSize(Frontier::Size size);
    Frontier::Size getSize() const { return m_size; }
    Geek::Gfx::Surface* getSurface() const { return m_surface; }

    Menu* getMenu() { return m_menu; }
    void setMenu(Menu* menu);
    void openContextMenu(Geek::Vector2D pos, Menu* menu);

    void postEvent(Frontier::Event* event);
    virtual bool handleEvent(Frontier::Event* event);
    sigc::signal<bool> closeSignal() { return m_closeSignal; }

    virtual void gainedFocus();
    virtual void lostFocus();

    Geek::Vector2D getScreenPosition(Geek::Vector2D windowPos);
};

};

#endif
