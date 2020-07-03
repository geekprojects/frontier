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

#ifndef __FRONTIER_WINDOW_H_
#define __FRONTIER_WINDOW_H_

#include <vector>

#include <geek/gfx-surface.h>

#include <frontier/utils.h>
#include <frontier/events.h>
#include <frontier/theme.h>
#include <frontier/layer.h>

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

/**
 * \defgroup windows Windows
 */

/**
 * \brief Window flags
 */
enum WindowFlags
{
    WINDOW_BORDER      = 1, /// Window should have a border
    WINDOW_RESIZEABLE  = 2, /// Window should be resizeable by the user
    WINDOW_TOOL_TIP    = 4, /// Window will be used as a tool tip
    WINDOW_FULL_SCREEN = 8, /// Window should be full screen

    WINDOW_NORMAL = WINDOW_BORDER | WINDOW_RESIZEABLE,
};

enum WindowCursor
{
    CURSOR_ARROW,
    CURSOR_POINTING,
    CURSOR_EDIT,
    CURSOR_RESIZE_HORIZONTAL,
    CURSOR_RESIZE_VERTICAL,
};

/**
 * \brief A representation of a Window on the screen
 *
 * \ingroup windows
 */
class FrontierWindow : public FrontierObject, public Geek::Logger
{
 private:
    FrontierEngineWindow* m_engineWindow;
    bool m_initialised;

    FrontierApp* m_app;

    std::wstring m_title;
    int m_flags;
    bool m_visible;

    Layer* m_rootLayer;
    std::vector<Layer*> m_layers;

    sigc::signal<void> m_closeSignal;
    Widget* m_content;
    Widget* m_activeWidget;
    Widget* m_mouseOverWidget;
    Widget* m_motionWidget;
    uint64_t m_motionTime;
    Frontier::WindowCursor m_currentCursor;

    uint64_t m_updateTimestamp;
    Geek::Mutex* m_drawMutex;
    bool m_updating;
    bool m_compositeSurface;
    Geek::Gfx::Surface* m_windowSurface;

    Widget* m_dragWidget;
    Geek::Gfx::Surface* m_dragSurface;
    Geek::Vector2D m_dragPosition;

    Menu* m_menu;
    MenuList* m_menuBar;

    sigc::signal<void> m_showSignal;
    sigc::signal<bool> m_gainedFocusSignal;
    sigc::signal<bool> m_lostFocusSignal;

    bool initInternal();
    void updateCursor();

    Widget* dragOver(Geek::Vector2D position, Widget* current, bool dropped);

 protected:
    virtual bool init();

 public:
    FrontierWindow(FrontierApp* app, std::wstring title, int flags);
    virtual ~FrontierWindow();

    std::wstring getTitle() const { return m_title; }
    bool hasBorder() const { return !!(m_flags & WINDOW_BORDER); }
    bool isResizeable() const { return !!(m_flags & WINDOW_RESIZEABLE); }
    bool isFullScreen() const { return !!(m_flags & WINDOW_FULL_SCREEN); }

    void setPosition(Geek::Vector2D position);
    Geek::Vector2D getPosition();
    Frontier::Rect getRect();

    void setContent(Widget* widget);
    Widget* getContent() const { return m_content; }
    void setActiveWidget(Widget* widget);
    Widget* getActiveWidget() const { return m_activeWidget; }
    void setMotionWidget(Widget* widget);
    void setMouseOver(Widget* widget);
    Widget* getMouseOverWidget() { return m_mouseOverWidget; }

    void dragWidget(Widget* widget);

    void show();
    void hide();
    void update(bool force = false);
    void requestUpdate();

    void setEngineWindow(FrontierEngineWindow* few) { m_engineWindow = few; }
    FrontierEngineWindow* getEngineWindow() { return m_engineWindow; }
    FrontierApp* getApp() const { return m_app; }

    void setSize(Frontier::Size size);
    Frontier::Size getSize() const { return m_rootLayer->getRect().getSize(); }
    Geek::Gfx::Surface* getSurface() { return m_windowSurface; }
    float getScaleFactor();
    Geek::Mutex* getDrawMutex() { return m_drawMutex; }

    Menu* getMenu() { return m_menu; }
    void setMenu(Menu* menu);
    void openContextMenu(Geek::Vector2D pos, Menu* menu);

    void addLayer(Layer* layer);
    void removeLayer(Layer* layer);
    std::vector<Layer*>& getLayers() { return m_layers; }

    void postEvent(Frontier::Event* event);
    virtual bool handleEvent(Frontier::Event* event);
    sigc::signal<void> closeSignal() { return m_closeSignal; }
    sigc::signal<void> showSignal() { return m_showSignal; }

    virtual void gainedFocus();
    virtual void lostFocus();

    Geek::Vector2D getScreenPosition(Geek::Vector2D windowPos);
};

};

#endif
