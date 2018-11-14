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

#ifndef __FRONTIER_WIDGETS_H_
#define __FRONTIER_WIDGETS_H_

#include <vector>

#include <frontier/frontier.h>

#include <sigc++/sigc++.h>

#define WIDGET_SIZE_UNLIMITED 0xffff

namespace Frontier {

class Menu;

enum TextAlign
{
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
};

enum DirtyFlag
{
    DIRTY_SIZE = 0x1,   // The size of the widget or its children have changed
    DIRTY_CONTENT = 0x2 // Just the contents of the widget needs redrawing
};

class Widget : public FrontierObject
{
 protected:
    FrontierApp* m_ui;
    FrontierWindow* m_window;
    Widget* m_parent;
    bool m_initialised;
    void* m_privateData;

    std::vector<Widget*> m_children;
    Menu* m_contextMenu;

    int m_x;
    int m_y;

    bool m_packed;
    Frontier::Size m_minSize;
    Frontier::Size m_maxSize;
    Frontier::Size m_setSize;

    int m_dirty;

    int m_margin;
    int m_padding;

    bool m_mouseOver;

    sigc::signal<void, bool> m_mouseEnterSignal;

    void initWidget(FrontierApp* app);
    void callInit();

 protected:
    virtual void init();

 public:
    Widget(FrontierApp* ui);
    Widget(FrontierWindow* window);
    virtual ~Widget();

    void setPrivateData(void* data) { m_privateData = data; }
    void* getPrivateData() { return m_privateData; }

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface);

    int getX() { return m_x; }
    int getY() { return m_y; }
    void setPosition(int x, int y) { m_x = x; m_y = y; }

    void setPacked(bool packed) { m_packed = packed; }
    bool getPacked() { return m_packed; }
    Frontier::Size setSize(Frontier::Size size);
    Frontier::Size getSize() { return m_setSize; }
    Frontier::Size getMinSize() { return m_minSize; }
    Frontier::Size getMaxSize() { return m_maxSize; }
    virtual int getWidth() { return m_setSize.width; }
    virtual int getHeight() { return m_setSize.height; }

    virtual void setMargin(int margin) { m_margin = margin; }
    virtual int getMargin() { return m_margin; }
    virtual void setPadding(int padding) { m_padding = padding; }
    virtual int getPadding() { return m_padding; }

    void setParent(Widget* w);
    Widget* getParent() { return m_parent; }

    void setWindow(FrontierWindow* window) { m_window = window; }
    FrontierWindow* getWindow();

    virtual Geek::Vector2D getAbsolutePosition();
    bool intersects(int x, int y);

    void setDirty();
    void setDirty(int flags, bool children = false);
    bool isDirty() { return !!(m_dirty); }
    bool isDirty(DirtyFlag flag) { return !!(m_dirty & flag); }
    void clearDirty();

    bool isActive();

    void setContextMenu(Menu* menu) { m_contextMenu = menu; }
    Menu* getContextMenu() { return m_contextMenu; }
    void openContextMenu();
    void openContextMenu(Geek::Vector2D pos);

    virtual Widget* handleMessage(Frontier::Message* msg);
    
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual sigc::signal<void, bool> signalMouseEnter() { return m_mouseEnterSignal; }
    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_POINTER; }

    virtual void dump(int level);
};

};

#endif
