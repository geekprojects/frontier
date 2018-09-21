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

class Widget
{
 protected:
    FrontierApp* m_ui;
    Widget* m_parent;

    std::vector<Widget*> m_children;

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

 public:
    Widget(FrontierApp* ui);
    virtual ~Widget();

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface);

    int getX() { return m_x; }
    int getY() { return m_y; }
    void setPosition(int x, int y) { m_x = x; m_y = y; }

    void setPacked(bool packed) { m_packed = packed; }
    bool getPacked() { return m_packed; }
    Frontier::Size setSize(Frontier::Size size);
    Frontier::Size getMinSize() { return m_minSize; }
    Frontier::Size getMaxSize() { return m_maxSize; }
    virtual int getWidth() { return m_setSize.width; }
    virtual int getHeight() { return m_setSize.height; }

    virtual void setMargin(int margin) { m_margin = margin; }
    virtual int getMargin() { return m_margin; }
    virtual void setPadding(int padding) { m_padding = padding; }
    virtual int getPadding() { return m_padding; }

    void setParent(Widget* w) { m_parent = w; }
    Widget* getParent() { return m_parent; }

    Geek::Vector2D getAbsolutePosition();
    bool intersects(int x, int y);

    void setDirty();
    void setDirty(int flags, bool children = false);
    bool isDirty() { return !!(m_dirty); }
    bool isDirty(DirtyFlag flag) { return !!(m_dirty & flag); }
    void clearDirty();

    virtual Widget* handleMessage(Frontier::Message* msg);
    
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual sigc::signal<void, bool> signalMouseEnter() { return m_mouseEnterSignal; }

    virtual void dump(int level);
};

class Frame : public Widget
{
 protected:
    bool m_horizontal;
    bool m_border;

    virtual void calculateSize();
    virtual void layout();

 public:
    Frame(FrontierApp* ui, bool horizontal);
    virtual ~Frame();

    void setBorder(bool border) { m_border = border; }

    virtual void add(Widget* widget);

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

class ResizeableFrame : public Frame
{
 protected:
    std::vector<float> m_sizes;

    // Dragging resize state
    bool m_dragging;
    int m_dragWidget;
    int m_dragPos;

    virtual void layout();

 public:
    ResizeableFrame(FrontierApp* ui, bool horizontal);
    virtual ~ResizeableFrame();

    virtual void add(Widget* widget);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

class Grid : Widget
{
 private:

 public:
    Grid(FrontierApp* ui);
    virtual ~Grid();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

class Button : public Widget
{
 protected:
    std::wstring m_text;
    bool m_state;

    sigc::signal<void> m_clickSignal;

 public:
    Button(FrontierApp* ui, std::wstring text);
    ~Button();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    virtual sigc::signal<void> clickSignal() { return m_clickSignal; }
};

class IconButton : public Button
{
 private:
    wchar_t m_icon;

 public:
    IconButton(FrontierApp* ui, wchar_t icon);
    ~IconButton();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

class Label : public Widget
{
 private:
    std::wstring m_text;
    TextAlign m_align;

    int m_lineHeight;

 public:
    Label(FrontierApp* ui, std::wstring text);
    Label(FrontierApp* ui, std::wstring text, TextAlign align);
    ~Label();

    void setText(std::wstring wtext);
    void setAlign(TextAlign align);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

struct ListItem
{
    virtual std::wstring getText() { return L""; }
};

struct TextListItem : public ListItem
{
    std::wstring m_text;
    std::wstring getText() { return m_text; }

    TextListItem() {}
    TextListItem(std::wstring text) { m_text = text; }
};

class List : public Widget
{
 private:
    std::vector<ListItem*> m_list;
    int m_selected;
    int m_itemHeight;

 public:
    List(FrontierApp* ui);
    ~List();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void clearItems();
    void addItem(ListItem* item);
    int getSelected() { return m_selected; }
    ListItem* getItem(int i) { return m_list.at(i); }
};

class ScrollBar : public Widget
{
 private:
    int m_min;
    int m_max;
    int m_pos;
    int m_size;
    bool m_dragging;

    int getControlPos();
    int getControlSize();
    int range() { return m_max - (m_min + m_size); }

    sigc::signal<void, int> m_changedPositionSignal;

 public:
    ScrollBar(FrontierApp* ui);
    ~ScrollBar();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void set(int min, int max, int size);
    void setPos(int pos);
    int getPos();

    virtual sigc::signal<void, int> changedPositionSignal() { return m_changedPositionSignal; }
};

class Scroller : public Widget
{
 private:

    ScrollBar* m_scrollBar;
    Widget* m_child;
    Geek::Gfx::Surface* m_childSurface;

    void checkSurfaceSize(bool highDPI);
    int getWidthOverhead() { return (m_scrollBar->getWidth() - 2); }

 public:
    Scroller(FrontierApp* ui);
    Scroller(FrontierApp* ui, Widget* child);
    ~Scroller();

    virtual void calculateSize();
    virtual void layout();
    //virtual void setWidth(int width);

    int getPos() { return m_scrollBar->getPos(); }

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void setChild(Widget* child);
};

struct Tab
{
    std::wstring title;
    Widget* content;
};

class Tabs : public Widget
{
 protected:
    unsigned int m_activeTab;
    std::vector<Tab> m_tabs;

    sigc::signal<void, Widget*> m_changeTabSignal;

    int getTabWidth();

 public:
    Tabs(FrontierApp* app);
    virtual ~Tabs();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void addTab(std::wstring title, Widget* content);

    Widget* getActiveTab()
    {
        if (m_tabs.empty())
        {
            return NULL;
        }
        if (m_activeTab >= m_tabs.size())
        {
            m_activeTab = m_tabs.size() - 1;
        }
        return m_tabs.at(m_activeTab).content;
    }

    virtual void dump(int level);

    virtual sigc::signal<void, Widget*> changeTabSignal() { return m_changeTabSignal; }
};

};

#endif
