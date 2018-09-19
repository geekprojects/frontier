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

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui)
{
    m_ui = ui;
    m_parent = NULL;

    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;

    m_minSize = Size(0, 0);
    m_maxSize = Size(0, 0);
    m_setSize = Size(0, 0);

    m_margin = 5;
    m_padding = 5;
}

Widget::~Widget()
{
}

void Widget::calculateSize()
{
printf("Widget::calculateSize: Not set!\n");
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

Geek::Vector2D Widget::getAbsolutePosition()
{
    Vector2D pos;
    pos.x = m_x;
    pos.y = m_y;

    if (m_parent != NULL)
    {
        pos += m_parent->getAbsolutePosition();
    }
    else
    {
        //pos += m_ui->getPosition();
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
    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;
    if (m_parent != NULL)
    {
        m_parent->setDirty();
    }
}

void Widget::setDirty(int dirty, bool children)
{
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

Widget* Widget::handleMessage(Message* msg)
{
    return NULL;
}

void Widget::onMouseEnter()
{
    m_mouseOver = true;
    m_mouseEnterSignal.emit(true);
setDirty();
}

void Widget::onMouseLeave()
{
    m_mouseOver = false;
    m_mouseEnterSignal.emit(false);
setDirty();
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


