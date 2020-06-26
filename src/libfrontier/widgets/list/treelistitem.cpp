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
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define TREELISTITEM_INDENT 15

TreeListItem::TreeListItem(FrontierApp* ui, std::wstring text) : TextListItem(ui, text)
{
    m_open = false;
}

TreeListItem::TreeListItem(FrontierApp* ui, Icon* icon, std::wstring text) : TextListItem(ui, icon, text)
{
    m_open = false;
}

TreeListItem::TreeListItem(FrontierWindow* win, std::wstring text) : TextListItem(win, text)
{
    m_open = false;
}

TreeListItem::TreeListItem(FrontierWindow* win, Icon* icon, std::wstring text) : TextListItem(win, icon, text)
{
    m_open = false;
}

TreeListItem::~TreeListItem()
{
}

void TreeListItem::addItem(ListItem* item)
{
    m_children.push_back(item);
    item->incRefCount();
    item->setParent(this);
    item->setList(m_list);
}

void TreeListItem::setOpen(bool open)
{
    m_open = open;
    setDirty();
}

void TreeListItem::calculateSize()
{
    TextListItem::calculateSize();
    m_titleHeight = m_minSize.height;

    m_minSize.width += TREELISTITEM_INDENT;
    if (m_open)
    {
        int childWidthMax = 0;
        for (Widget* item : m_children)
        {
            item->calculateSize();

            Size itemMin = item->getMinSize();
            m_minSize.height += itemMin.height;
            if (itemMin.width > childWidthMax)
            {
                childWidthMax = itemMin.width;
            }
        }
        m_minSize.width += childWidthMax;
    }
}

void TreeListItem::layout()
{
    int y = m_titleHeight;
    if (m_open)
    {
        for (Widget* item : m_children)
        {
            Size itemMin = item->getMinSize();
            Size itemMax = item->getMaxSize();
            Size itemSize = Size(m_setSize.width - (TREELISTITEM_INDENT * 1), itemMin.height);
            itemSize.setMax(itemMin);
            itemSize.setMin(itemMax);
            item->setSize(itemSize);
            item->setPosition((TREELISTITEM_INDENT * 1), y);
            item->layout();
            y += itemSize.height;
        }
    }
}

bool TreeListItem::draw(Geek::Gfx::Surface* surface)
{
#if 0
    log(DEBUG, "draw: Drawing label...");
#endif

    // Draw text & icon
    SurfaceViewPort viewport(surface, TREELISTITEM_INDENT, 0, m_setSize.width - TREELISTITEM_INDENT, m_titleHeight);
    TextListItem::draw(&viewport);

    if (!m_children.empty())
    {
        uint32_t icon = FRONTIER_ICON_CARET_RIGHT;
        if (m_open)
        {
            icon = FRONTIER_ICON_CARET_DOWN;
        }
        m_app->getTheme()->drawIcon(surface, 1, 2, icon, false);
    }

    if (m_open)
    {
        for (Widget* item : m_children)
        {
#if 0
            log(DEBUG, "draw: item: %d, %d size=%d,%d", item->getX(), item->getY(), item->getWidth(), item->getHeight());
#endif
            SurfaceViewPort viewport(surface, item->getX(), item->getY(), item->getWidth(), item->getHeight());
            item->draw(&viewport);
        }
    }

    return true;
}

Widget* TreeListItem::handleEvent(Frontier::Event* event)
{
    if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON ||
        event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;
        Vector2D thisPos = getAbsolutePosition();
        int widgetx = mouseEvent->x - thisPos.x;
        int widgety = mouseEvent->y - thisPos.y;

        if (widgety < m_titleHeight)
        {
            if (widgetx > TREELISTITEM_INDENT)
            {
                return TextListItem::handleEvent(event);
            }
            else
            {
                if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON && ((MouseButtonEvent*)event)->direction)
                {
                    m_open = !m_open;
                    setDirty();
                    return this;
                }
            }
        }
        else
        {
            if (!m_open)
            {
                // Shouldn't be here!
                return NULL;
            }
            int x = mouseEvent->x;
            int y = mouseEvent->y;

            for (Widget* child : m_children)
            {
                if (child->intersects(x, y))
                {
                    return child->handleEvent(event);
                }
            }

        }
    }
    return NULL;
}


