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
#include <map>

#include <frontier/frontier.h>
#include <frontier/styles.h>

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

class Widget : public FrontierObject, public Geek::Logger
{
 protected:
    FrontierApp* m_app;
    std::wstring m_widgetName;
    std::wstring m_widgetId;
    std::set<std::wstring> m_widgetClasses;

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

    uint64_t m_styleTimestamp;
    StyleRule m_widgetStyleProperties;
    std::map<std::string, int64_t> m_cachedStyleProperties;

    bool m_mouseOver;
    bool m_selected;

    sigc::signal<void, bool> m_mouseEnterSignal;
    sigc::signal<void> m_activeSignal;
    sigc::signal<void> m_inactiveSignal;

    sigc::signal<bool, Widget*, Geek::Vector2D> m_dragOverSignal;
    sigc::signal<bool, Widget*, Geek::Vector2D> m_dragDropSignal;
    sigc::signal<bool, Widget*> m_dragCancelledSignal;
    sigc::signal<void, Widget*> m_clickSignal;
    sigc::signal<void, Widget*> m_doubleClickSignal;

    void initWidget(FrontierApp* app, std::wstring widgetName);
    void callInit();

    Size getBorderSize();
    bool drawBorder(Geek::Gfx::Surface* surface);

 protected:
    virtual void init();

 public:
    Widget(FrontierApp* ui, std::wstring name);
    Widget(FrontierWindow* window, std::wstring name);
    virtual ~Widget();

    std::wstring getWidgetName() { return m_widgetName; }
    void setPrivateData(void* data) { m_privateData = data; }
    void* getPrivateData() const { return m_privateData; }

    virtual std::vector<Widget*> getChildren() { return m_children; }

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface);
    virtual bool draw(Geek::Gfx::Surface* surface, Rect visible);

    bool hasStyle(std::string style);
    int64_t getStyle(std::string style);
    void setStyle(std::string style, int64_t value);
    void setWidgetId(std::wstring id) { m_widgetId = id; }
    std::wstring getWidgetId() { return m_widgetId; }
    bool hasWidgetClass(std::wstring className);
    void setWidgetClass(std::wstring className);
    void clearWidgetClass(std::wstring className);
    std::set<std::wstring> getWidgetClasses() { return m_widgetClasses; }
    StyleRule* getWidgetStyle() { return &m_widgetStyleProperties; }
    std::map<std::string, int64_t>& getStyleProperties();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    void setPosition(int x, int y) { m_x = x; m_y = y; }

    void setPacked(bool packed) { m_packed = packed; }
    bool getPacked() const { return m_packed; }
    Frontier::Size setSize(Frontier::Size size);
    Frontier::Size getSize() const { return m_setSize; }
    Frontier::Size getMinSize() { return m_minSize; }
    Frontier::Size getMaxSize() const { return m_maxSize; }
    virtual int getWidth() const { return m_setSize.width; }
    virtual int getHeight() const { return m_setSize.height; }

    void setParent(Widget* w);
    Widget* getParent() const { return m_parent; }
    Widget* findParent(const std::type_info& type);

    void setWindow(FrontierWindow* window) { m_window = window; }
    FrontierWindow* getWindow();
    FrontierApp* getApp() { return m_app; }

    virtual Geek::Vector2D getAbsolutePosition() const;
    bool intersects(int x, int y) const;

    void setDirty();
    void setDirty(int flags, bool children = false);
    bool isDirty() const { return !!(m_dirty); }
    bool isDirty(DirtyFlag flag) const { return !!(m_dirty & flag); }
    void clearDirty();

    void setActive();
    bool isActive();
    virtual void activateNext(Widget* activeChild = NULL);

    bool isMouseOver() { return m_mouseOver; }
    bool isSelected() { return m_selected; }

    void setContextMenu(Menu* menu) { m_contextMenu = menu; }
    Menu* getContextMenu() const { return m_contextMenu; }
    void openContextMenu();
    void openContextMenu(Geek::Vector2D pos);

    virtual Widget* handleEvent(Frontier::Event* msg);
    
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual sigc::signal<void, bool> signalMouseEnter() { return m_mouseEnterSignal; }
    virtual sigc::signal<void> signalActive() { return m_activeSignal; }
    virtual sigc::signal<void> signalInactive() { return m_inactiveSignal; }

    virtual sigc::signal<bool, Widget*, Geek::Vector2D> dragOverSignal() { return m_dragOverSignal; }
    virtual sigc::signal<bool, Widget*, Geek::Vector2D> dragDropSignal() { return m_dragDropSignal; }
    virtual sigc::signal<bool, Widget*> dragCancelledSignal() { return m_dragCancelledSignal; }
    virtual sigc::signal<void, Widget*> clickSignal() { return m_clickSignal; }
    virtual sigc::signal<void, Widget*> doubleClickSignal() { return m_doubleClickSignal; }

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_POINTER; }

    virtual void dump(int level);
};

};

#endif
