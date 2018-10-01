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

List::List(FrontierApp* ui) : Widget(ui)
{
    m_selected = NULL;
}

List::List(FrontierWindow* window) : Widget(window)
{
    m_selected = NULL;
}

List::~List()
{
}

void List::calculateSize()
{
    vector<ListItem*>::iterator it;

    m_minSize.set(0, 0);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_minSize.height = 0;
    for (it = m_list.begin(); it != m_list.end(); it++)
    {
        ListItem* item = *it;
        item->calculateSize();
        Size itemMin = item->getMinSize();
        m_minSize.setMax(itemMin);
        m_minSize.height += itemMin.height;
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
        printf("List::layout: itemSize(1): %d,%d, min=%d,%d, max=%d,%d\n", itemSize.width, itemSize.height, itemMin.width, itemMin.height, itemMax.width, itemMax.height);
#endif
        itemSize.setMin(itemMax);
        itemSize.setMax(itemMin);
#if 0
printf("List::layout: itemSize(2): %d,%d\n", itemSize.width, itemSize.height);
#endif
        item->setSize(itemSize);
        item->setPosition(x, y);

        item->layout();

        y += itemSize.height;
    }
}

bool List::draw(Surface* surface)
{
    //surface->drawRect(0, 0, m_setSize.width, m_setSize.height, 0xffffffff);
    m_ui->getTheme()->drawBackground(surface);

    int idx;
    vector<ListItem*>::iterator it;
    for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
    {
        ListItem* item = *it;
#if 0
        printf("List::draw: itemSize: %d,%d\n", item->getWidth(), item->getHeight());
#endif
        SurfaceViewPort viewport(surface, item->getX(), item->getY(), item->getWidth(), item->getHeight());
        item->draw(&viewport);
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

#if 0
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            Vector2D pos = getAbsolutePosition();
            int ey = imsg->event.button.y - pos.y;
            int selected = -1;
            bool hasSelected = false;
            int y = 2;

            int idx;
            vector<ListItem*>::iterator it;
            for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
            {
                if (ey >= y && ey < y + m_itemHeight)
                {
                    selected = idx;
                    hasSelected = true;
                    break;
                }
                y += m_itemHeight;
            }

            if (hasSelected && (m_selected != selected || imsg->event.button.doubleClick || imsg->event.button.button == 3))
            {
                printf("List::handleMessage: Selected item %d, doubleClick=%d\n", m_selected, imsg->event.button.doubleClick);

                setDirty(DIRTY_CONTENT);

                m_selected = selected;

                UIMessage* buttonMessage = new UIMessage();
                buttonMessage->messageType = FRONTIER_MSG_UI;
                buttonMessage->uiMessageType = FRONTIER_MSG_UI_LIST_SELECTED;
                buttonMessage->widget = this;
                buttonMessage->source = msg;
                buttonMessage->list.selected = m_selected;
                buttonMessage->list.itemY = y;
                m_ui->postMessage(buttonMessage);
            }
        }
    }
#endif

    return this;
}

void List::clearItems()
{
    m_list.clear();
    setDirty();
}

void List::addItem(ListItem* item)
{
    m_list.push_back(item);
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

ListItem::ListItem(FrontierApp* ui) : Widget(ui)
{
    m_selected = false;
}

ListItem::ListItem(FrontierWindow* win) : Widget(win)
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
            //if (imsg->event.button.direction)
            {
                if (m_selected)
                {
                    // Ignore
                }
                else
                {
                    setSelected();
                    m_clickSignal.emit(this);
                    return this;
                }
            }
        }
    }
    return NULL;
}

