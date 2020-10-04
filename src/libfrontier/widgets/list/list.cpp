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


#include <frontier/frontier.h>
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

FRONTIER_WIDGET(List, Frontier::List)

List::List(FrontierApp* ui) : Widget(ui, L"List")
{
    m_selected = NULL;
    m_horizontal = false;
    m_listMutex = Thread::createMutex();
}

List::List(FrontierApp* ui, bool horizontal) : Widget(ui, L"List")
{
    m_selected = NULL;
    m_horizontal = horizontal;
    m_listMutex = Thread::createMutex();
}

List::~List()
{
    clearItems(false);
}

void List::calculateSize()
{
    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);
    //m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_listMutex->lock();

    for (Widget* item : m_children)
    {
        if (item->isDirty(DIRTY_SIZE))
        {
            item->calculateSize();
        }

        Size itemMin = item->getMinSize();
        Size itemMax = item->getMaxSize();

        if (!m_horizontal)
        {
            m_minSize.setMaxWidth(itemMin);
            m_maxSize.setMaxWidth(itemMax);

            m_minSize.height += itemMin.height;

            if (itemMax.height == WIDGET_SIZE_UNLIMITED)
            {
                m_maxSize.height = WIDGET_SIZE_UNLIMITED;
            }
            else if (m_maxSize.height < WIDGET_SIZE_UNLIMITED)
            {
                m_maxSize.height += itemMin.height;
            }
        }
        else
        {
            m_minSize.setMaxHeight(itemMin);
            m_maxSize.setMaxHeight(itemMax);

            m_minSize.width += itemMin.width;

            if (itemMax.width == WIDGET_SIZE_UNLIMITED)
            {
                m_maxSize.width = WIDGET_SIZE_UNLIMITED;
            }
            else if (m_maxSize.width < WIDGET_SIZE_UNLIMITED)
            {
                m_maxSize.width += itemMin.height;
            }

        }
    }
    m_listMutex->unlock();

    Size borderSize = getBorderSize();
    m_minSize += borderSize;
    m_maxSize += borderSize;
}

void List::layout()
{
    int x = 2;
    int y = 2;

    m_listMutex->lock();
    int idx;
    vector<Widget*>::iterator it;
    for (it = m_children.begin(), idx = 0; it != m_children.end(); ++it, idx++)
    {
        Widget* item = *it;

        Size itemMin = item->getMinSize();
        Size itemMax = item->getMaxSize();

        Size itemSize;
        if (!m_horizontal)
        {
            itemSize = Size(m_setSize.width, itemMin.height);
#if 0
            log(DEBUG, "layout: itemSize(1): %d,%d, min=%d,%d, max=%d,%d", itemSize.width, itemSize.height, itemMin.width, itemMin.height, itemMax.width, itemMax.height);
#endif
            itemSize.setMin(itemMax);
            itemSize.setMax(itemMin);
        }
        else
        {
            itemSize = Size(itemMin.width, m_setSize.height);
#if 0
            log(DEBUG, "layout: itemSize(1): %d,%d, min=%d,%d, max=%d,%d", itemSize.width, itemSize.height, itemMin.width, itemMin.height, itemMax.width, itemMax.height);
#endif
            itemSize.setMin(itemMax);
            itemSize.setMax(itemMin);
    }

#if 0
        log(DEBUG, "layout: itemSize(2): %d,%d", itemSize.width, itemSize.height);
#endif
        item->setSize(itemSize);
        item->setPosition(x, y);

        item->layout();

        if (!m_horizontal)
        {
            y += itemSize.height;
        }
        else
        {
            x += itemSize.width;
        }
    }
    m_listMutex->unlock();
}

bool List::draw(Surface* surface, Rect visible)
{
    drawBorder(surface);

    m_listMutex->lock();
    int idx;
    vector<Widget*>::iterator it;
    for (it = m_children.begin(), idx = 0; it != m_children.end(); ++it, idx++)
    {
        Widget* item = *it;
#if 0
        log(DEBUG, "draw: %d,%d, itemSize: %d,%d", item->getX(), item->getY(), item->getWidth(), item->getHeight());
#endif

        if (item->getX() >= visible.x - item->getWidth() && item->getY() >= visible.y - item->getHeight())
        {
            if (!m_horizontal)
            {
                if (item->getY() > visible.y + visible.height)
                {
                    break;
                }
            }
            else
            {
                if (item->getX() > visible.x + visible.width)
                {
                    break;
                }
            }
            SurfaceViewPort viewport(surface, item->getX(), item->getY(), item->getWidth(), item->getHeight());
            item->draw(&viewport);
        }
    }
    m_listMutex->unlock();
    return true;
}

Widget* List::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;

        m_listMutex->lock();

        for (Widget* child : m_children)
        {
            if (child->intersects(mouseEvent->x, mouseEvent->y))
            {
                m_listMutex->unlock();
                return child->handleEvent(event);
            }
        }
        m_listMutex->unlock();

        if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
        {
            return this;
        }
    }

    return this;
}

void List::clearItems(bool setDirty)
{
    m_listMutex->lock();
    for (Widget* item : m_children)
    {
        item->decRefCount();
    }

    m_children.clear();
    m_listMutex->unlock();

    m_selected = NULL;

    if (setDirty)
    {
        this->setDirty();
    }
}

void List::addItem(ListItem* item)
{
    m_listMutex->lock();
    m_children.push_back(item);
    item->incRefCount();
    item->setParent(this);
    item->setList(this);
    m_listMutex->unlock();

    setDirty(DIRTY_CONTENT);
}

void List::setSelected(ListItem* item)
{
    if (m_selected != NULL)
    {
        m_selected->clearSelected(false);
    }
    m_selected = item;
    setDirty(DIRTY_CONTENT);
}

void List::clearSelected(ListItem* item)
{
    if (m_selected == item)
    {
        m_selected = NULL;
        if (item != NULL)
        {
            item->clearSelected(false);
        }
    }
    setDirty(DIRTY_CONTENT);
}

ListItem::ListItem(FrontierApp* ui) : Widget(ui, L"ListItem")
{
    m_selected = false;
    m_list = NULL;
}

ListItem::~ListItem() = default;

void ListItem::setList(List* list)
{
    m_list = list;
}

void ListItem::setSelected(bool updateList)
{
    m_selected = true;

    if (updateList && m_list != NULL)
    {
        m_list->setSelected(this);
    }
    setDirty(DIRTY_CONTENT | DIRTY_STYLE);
}

void ListItem::clearSelected(bool updateList)
{
    m_selected = false;

    if (updateList && m_list != NULL)
    {
        m_list->clearSelected(this);
    }
    setDirty(DIRTY_CONTENT | DIRTY_STYLE);
}

Widget* ListItem::handleEvent(Frontier::Event* event)
{
    if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON)
    {
        MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
        log(DEBUG,
            "handleMessage: direction=%d, buttons=%d, doubleClick=%d",
            mouseButtonEvent->direction,
            mouseButtonEvent->buttons,
            mouseButtonEvent->doubleClick);
        if (mouseButtonEvent->direction)
        {
            if (m_selected)
            {
                // Ignore
                if (mouseButtonEvent->doubleClick)
                {
                    doubleClickSignal().emit(this);
                }
            }
            else
            {
                setSelected();

                if (mouseButtonEvent->doubleClick)
                {
                    doubleClickSignal().emit(this);
                }
                else
                {
                    clickSignal().emit(this);
                }
                if (m_list != NULL)
                {
                    m_list->selectSignal().emit(this);
                }
                return this;
            }
        }
        else
        {
            if (mouseButtonEvent->buttons == BUTTON_RIGHT)
            {
                m_list->contextMenuSignal().emit(this, Vector2D(mouseButtonEvent->x, mouseButtonEvent->y));
                return this;
            }
            return NULL;
        }
    }
    return this;
}




