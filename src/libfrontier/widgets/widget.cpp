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

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui)
{
    initWidget(ui);
}

Widget::Widget(FrontierWindow* window)
{
    initWidget(window->getApp());
    m_window = window;
}

Widget::~Widget()
{
}

void Widget::initWidget(FrontierApp* app)
{
    m_ui = app;
    m_window = NULL;
    m_parent = NULL;
    m_contextMenu = NULL;

    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;

    m_minSize = Size(0, 0);
    m_maxSize = Size(0, 0);
    m_setSize = Size(0, 0);

    m_margin = 5;
    m_padding = 5;

    m_mouseOver = false;

    m_initialised = false;
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

void Widget::setParent(Widget* widget)
{
    m_parent = widget;

    callInit();
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

Geek::Vector2D Widget::getAbsolutePosition()
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

bool Widget::intersects(int x, int y)
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

    ContextMenu* cm = m_ui->getContextMenuWindow();
    cm->setMenu(m_contextMenu);

    cm->setSize(Size(0, 0));
    cm->show();

    Vector2D screenPos = getWindow()->getScreenPosition(pos);
    cm->setPosition(screenPos);
}

Widget* Widget::handleMessage(Message* msg)
{
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
    printf("%s: %p: x=%d, y=%d, size=%s\n", spaces.c_str(), this, m_x, m_y, m_setSize.toString().c_str());

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        (*it)->dump(level + 1);
    }

}


