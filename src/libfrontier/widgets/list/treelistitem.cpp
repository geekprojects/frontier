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

TreeListItem::TreeListItem(FrontierApp* ui, uint32_t icon, std::wstring text) : TextListItem(ui, icon, text)
{
    m_open = false;
}

TreeListItem::TreeListItem(FrontierWindow* win, std::wstring text) : TextListItem(win, text)
{
    m_open = false;
}

TreeListItem::TreeListItem(FrontierWindow* win, uint32_t icon, std::wstring text) : TextListItem(win, icon, text)
{
    m_open = false;
}

TreeListItem::~TreeListItem()
{
}

void TreeListItem::addItem(ListItem* item)
{
    m_items.push_back(item);
    item->setParent(this);
    item->setList(m_list);
}

void TreeListItem::calculateSize()
{
    TextListItem::calculateSize();
    m_titleHeight = m_minSize.height;

    m_minSize.width += TREELISTITEM_INDENT;
if (m_open)
{
    vector<ListItem*>::iterator it;
    for (it = m_items.begin(); it != m_items.end(); it++)
    {
        ListItem* item = *it;
        item->calculateSize();

        Size itemMin = item->getMinSize();
        //Size itemMax = item->getMaxSize();
        m_minSize.height += itemMin.height;
    }
}
}

void TreeListItem::layout()
{
    int y = m_titleHeight;
if (m_open)
{
    vector<ListItem*>::iterator it;
    for (it = m_items.begin(); it != m_items.end(); it++)
    {
        ListItem* item = *it;
        Size itemMin = item->getMinSize();
        Size itemMax = item->getMaxSize();
        Size itemSize = Size(m_setSize.width - (TREELISTITEM_INDENT * 2), itemMin.height);
        itemSize.setMax(itemMin);
        itemSize.setMin(itemMax);
        item->setSize(itemSize);
        item->setPosition((TREELISTITEM_INDENT * 2), y);
        item->layout();
        y += itemSize.height;
    }
}
}

bool TreeListItem::draw(Geek::Gfx::Surface* surface)
{
#if 0
    printf("TreeListItem::draw: Drawing label...\n");
#endif

    // Draw text & icon
    SurfaceViewPort viewport(surface, TREELISTITEM_INDENT, 0, m_setSize.width - TREELISTITEM_INDENT, m_titleHeight);
    TextListItem::draw(&viewport);

    uint32_t icon = FRONTIER_ICON_CARET_RIGHT;
    if (m_open)
    {
        icon = FRONTIER_ICON_CARET_DOWN;
    }
    m_ui->getTheme()->drawIcon(surface, 1, 2, icon, false);

    if (m_open)
    {
        vector<ListItem*>::iterator it;
        for (it = m_items.begin(); it != m_items.end(); it++)
        {
            ListItem* item = *it;
#if 0
            printf("TreeListItem::draw: item: %d, %d size=%d,%d\n", item->getX(), item->getY(), item->getWidth(), item->getHeight());
#endif
            SurfaceViewPort viewport(surface, item->getX(), item->getY(), item->getWidth(), item->getHeight());
            item->draw(&viewport);
        }
    }

    return true;
}

Widget* TreeListItem::handleMessage(Frontier::Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
        {
            Vector2D thisPos = getAbsolutePosition();
            int widgetx = imsg->event.button.x - thisPos.x;
            int widgety = imsg->event.button.y - thisPos.y;

            if (widgety < m_titleHeight)
            {
                if (widgetx > TREELISTITEM_INDENT)
                {
                    return TextListItem::handleMessage(msg);
                }
                else
                {
                    if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON && imsg->event.button.direction)
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
                int x = imsg->event.button.x;
                int y = imsg->event.button.y;

                vector<ListItem*>::iterator it;
                for (it = m_items.begin(); it != m_items.end(); it++)
                {
                    ListItem* child = *it;
                    if (child->intersects(x, y))
                    {
                        return child->handleMessage(msg);
                    }
                }

            }
        }
    }
    return NULL;
}


