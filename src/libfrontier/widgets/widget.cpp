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


#include <frontier/frontier.h>
#include <frontier/widgets.h>
#include <frontier/contextmenu.h>

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui, wstring widgetName) : Logger(L"Widget[" + widgetName + L"]")
{
    initWidget(ui, widgetName);
}

Widget::Widget(FrontierWindow* window, wstring widgetName) : Logger(L"Widget[" + widgetName + L"]")
{
    initWidget(window->getApp(), widgetName);
    m_window = window;
}

Widget::~Widget()
{
    for (Widget* child : m_children)
    {
        child->decRefCount();
        child->setParent(NULL);
    }
    m_children.clear();
}

void Widget::initWidget(FrontierApp* app, wstring widgetName)
{
    m_app = app;
    m_widgetName = widgetName;

    m_window = NULL;
    m_parent = NULL;
    m_contextMenu = NULL;

    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;

    m_minSize = Size(0, 0);
    m_maxSize = Size(0, 0);
    m_setSize = Size(0, 0);

    setStyle(STYLE_MARGIN, m_app->getTheme()->getMargin());
    setStyle(STYLE_PADDING, m_app->getTheme()->getPadding());

    m_mouseOver = false;

    m_initialised = false;

    if (m_app != NULL)
    {
        m_app->registerObject(this);
    }
}

void Widget::init()
{
}

void Widget::calculateSize()
{
}

void Widget::layout()
{
}

Size Widget::setSize(Size size)
{
    calculateSize();

    // Clip the specified size to our min/max
    size.setMax(m_minSize);
    size.setMin(m_maxSize);

    m_setSize = size;

    return size;
}

bool Widget::draw(Geek::Gfx::Surface* surface, Rect visible)
{
    return draw(surface);
}

bool Widget::draw(Geek::Gfx::Surface* surface)
{
    return true;
}

void Widget::callInit()
{
    if (!m_initialised)
    {
        m_initialised = true;
        init();
    }
}

bool Widget::hasStyle(StyleAttribute style)
{
    return (m_styles.find(style) != m_styles.end());
}

uint64_t Widget::getStyle(StyleAttribute style)
{
    auto it = m_styles.find(style);
    if (it != m_styles.end())
    {
        return it->second;
    }
    return (uint64_t)-1ll;
}

void Widget::setStyle(StyleAttribute style, uint64_t value)
{
    auto it = m_styles.find(style);
    if (it != m_styles.end())
    {
        m_styles.erase(it);
    }
    m_styles.insert(make_pair(style, value));
}

void Widget::setParent(Widget* widget)
{
    m_parent = widget;

    callInit();
}

Widget* Widget::findParent(const type_info& type)
{
    if (m_parent == NULL)
    {
        return NULL;
    }

    if (typeid(*m_parent).hash_code() == type.hash_code())
    {
        return m_parent;
    }
    return m_parent->findParent(type);;
}

FrontierWindow* Widget::getWindow()
{
    if (m_window != NULL)
    {
        return m_window;
    }

    if (m_parent != NULL)
    {
        m_window = m_parent->getWindow();
        return m_window;
    }

    return NULL;
}

Geek::Vector2D Widget::getAbsolutePosition() const
{
    Vector2D pos;
    pos.x = m_x;
    pos.y = m_y;

    if (m_parent != NULL)
    {
        pos += m_parent->getAbsolutePosition();
    }

    return pos;
}

bool Widget::intersects(int x, int y) const
{
    Vector2D thisPos = getAbsolutePosition();
    int x1 = thisPos.x;
    int y1 = thisPos.y;
    int x2 = x1 + getWidth();
    int y2 = y1 + getHeight();
    return (x >= x1 && y >= y1 && x < x2 && y < y2);
}

void Widget::setDirty()
{
    callInit();
    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;
    if (m_parent != NULL)
    {
        m_parent->setDirty();
    }
}

void Widget::setDirty(int dirty, bool children)
{
    callInit();
    m_dirty |= dirty;

    if (children)
    {
        vector<Widget*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); it++)
        {
            (*it)->setDirty(dirty, true);
        }
    }
    else
    {
        if (m_parent != NULL)
        {
            m_parent->setDirty(dirty);
        }
    }
}

void Widget::clearDirty()
{
    m_dirty = false;

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        (*it)->clearDirty();
    }
}

bool Widget::isActive()
{
    FrontierWindow* window = getWindow();
    if (window != NULL)
    {
        return (window->getActiveWidget() == this);
    }
    return false;
}

void Widget::openContextMenu()
{
    openContextMenu(getAbsolutePosition());
}

void Widget::openContextMenu(Geek::Vector2D pos)
{
    if (m_contextMenu == NULL)
    {
        return;
    }

    getWindow()->openContextMenu(pos, m_contextMenu);
}

Widget* Widget::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            if (mouseButtonEvent->direction)
            {
                if (mouseButtonEvent->doubleClick)
                {
                    m_doubleClickSignal.emit(this);
                }
                else
                {
                    m_clickSignal.emit(this);
                }
            }
        } break;

        default:
            break;
    }
    return NULL;
}

void Widget::onMouseEnter()
{
    m_mouseOver = true;
    m_mouseEnterSignal.emit(true);
    setDirty(DIRTY_CONTENT);
}

void Widget::onMouseLeave()
{
    m_mouseOver = false;
    m_mouseEnterSignal.emit(false);
    setDirty(DIRTY_CONTENT);
}

void Widget::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }

    log(Geek::DEBUG, "%s%s(%p): x=%d, y=%d, size=%s", spaces.c_str(), m_widgetName.c_str(), this, m_x, m_y, m_setSize.toString().c_str());

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        (*it)->dump(level + 1);
    }

}


