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

List::List(FrontierApp* ui) : Widget(ui, L"List")
{
    m_selected = NULL;
}

List::List(FrontierWindow* window) : Widget(window, L"List")
{
    m_selected = NULL;
}

List::~List()
{
    clearItems(false);
}

void List::calculateSize()
{
    vector<ListItem*>::iterator it;

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);
    //m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    for (it = m_list.begin(); it != m_list.end(); it++)
    {
        ListItem* item = *it;
        item->calculateSize();

        Size itemMin = item->getMinSize();
        m_minSize.setMaxWidth(itemMin);
        m_minSize.height += itemMin.height;

        Size itemMax = item->getMaxSize();
        m_maxSize.setMaxWidth(itemMax);
        if (itemMax.height == WIDGET_SIZE_UNLIMITED)
        {
            m_maxSize.height = WIDGET_SIZE_UNLIMITED;
        }
        else if (m_maxSize.height < WIDGET_SIZE_UNLIMITED)
        {
            m_maxSize.height += itemMin.height;
        }
    }

    m_minSize.width += 2 * 2;
    m_minSize.height += 2 * 2;
}

void List::layout()
{
    int x = 2;
    int y = 2;

    vector<ListItem*>::iterator it;
    int idx;
    for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
    {
        ListItem* item = *it;

        Size itemMin = item->getMinSize();
        Size itemMax = item->getMaxSize();

        Size itemSize = Size(m_setSize.width, itemMin.height);
#if 0
        log(DEBUG, "layout: itemSize(1): %d,%d, min=%d,%d, max=%d,%d", itemSize.width, itemSize.height, itemMin.width, itemMin.height, itemMax.width, itemMax.height);
#endif
        itemSize.setMin(itemMax);
        itemSize.setMax(itemMin);
#if 0
        log(DEBUG, "layout: itemSize(2): %d,%d", itemSize.width, itemSize.height);
#endif
        item->setSize(itemSize);
        item->setPosition(x, y);

        item->layout();

        y += itemSize.height;
    }
}

bool List::draw(Surface* surface, Rect visible)
{
    m_app->getTheme()->drawBackground(surface);

    int idx;
    vector<ListItem*>::iterator it;
    for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
    {
        ListItem* item = *it;
#if 0
        log(DEBUG, "draw: %d,%d, itemSize: %d,%d", item->getX(), item->getY(), item->getWidth(), item->getHeight());
#endif

        if (item->getX() >= visible.x - item->getWidth() && item->getY() >= visible.y - item->getHeight())
        {
            if (item->getY() > visible.y + visible.height)
            {
                break;
            }
            SurfaceViewPort viewport(surface, item->getX(), item->getY(), item->getWidth(), item->getHeight());
            item->draw(&viewport);
        }
    }
    return true;
}

Widget* List::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_WHEEL)
        {
            int x = imsg->event.button.x;
            int y = imsg->event.button.y;

            vector<ListItem*>::iterator it;
            for (it = m_list.begin(); it != m_list.end(); it++)
            {
                ListItem* child = *it;
                if (child->intersects(x, y))
                {
                    return child->handleMessage(msg);
                }
            }
            if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
            {
                return this;
            }
        }
    }

    return this;
}

void List::clearItems(bool setDirty)
{
    for (ListItem* item : m_list)
    {
        item->decRefCount();
    }

    m_list.clear();
    m_selected = NULL;

    if (setDirty)
    {
        this->setDirty();
    }
}

void List::addItem(ListItem* item)
{
    m_list.push_back(item);
    item->incRefCount();
    item->setParent(this);
    item->setList(this);

    setDirty();
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
    m_selected = NULL;
}

ListItem::ListItem(FrontierApp* ui) : Widget(ui, L"ListItem")
{
    m_selected = false;
}

ListItem::ListItem(FrontierWindow* win) : Widget(win, L"ListItem")
{
    m_selected = false;
}

ListItem::~ListItem()
{
}

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
        setDirty(DIRTY_CONTENT);
    }
}

void ListItem::clearSelected(bool updateList)
{
    m_selected = false;

    if (updateList && m_list != NULL)
    {
        m_list->clearSelected(this);
        setDirty(DIRTY_CONTENT);
    }
}

Widget* ListItem::handleMessage(Frontier::Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            log(DEBUG, "handleMessage: direction=%d, buttons=%d", imsg->event.button.direction, imsg->event.button.buttons);
            if (imsg->event.button.direction)
            {
                if (m_selected)
                {
                    // Ignore
                }
                else
                {
                    setSelected();

                    m_clickSignal.emit(this);
                    if (m_list != NULL)
                    {
                        m_list->selectSignal().emit(this);
                    }
                    return this;
                }
            }
            else
            {
                if (imsg->event.button.buttons == BUTTON_RIGHT)
                {
                    m_list->contextMenuSignal().emit(this, Vector2D(imsg->event.button.x, imsg->event.button.y));
                    return this;
                }
                return NULL;
            }
        }
    }
    return this;
}




