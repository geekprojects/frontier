/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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
#include <frontier/widgets/tabs.h>

using namespace std;
using namespace Geek;
using namespace Frontier;

FRONTIER_WIDGET(Tab, Frontier::Tab)

#define TAB_SIZE 22

Tab::Tab(FrontierApp* app)
    : Widget(app, L"Tab")
{
    m_icon = NULL;
    m_closeable = false;
    m_mouseDown = false;
}

Tab::Tab(Tabs* tabs, wstring title, Icon* icon, Widget* content, bool closeable)
    : Widget(tabs->getApp(), L"Tab")
{
    setParent(tabs);

    setTitle(title);
    m_icon = icon;
    m_closeable = closeable;
    m_mouseDown = false;

    setContent(content);
}

Tab::Tab(FrontierApp* app, wstring title, Icon* icon, Widget* content, bool closeable)
    : Widget(app, L"Tab")
{
    setTitle(title);
    m_icon = icon;
    m_closeable = closeable;
    m_mouseDown = false;

    setContent(content);
}

Tab::~Tab()
{
}

void Tab::calculateSize()
{
    BoxModel boxModel = getBoxModel();
    int maxTabSize = getStyle("max-width").asInt();

    m_minSize.width = boxModel.getWidth();
    m_minSize.height = boxModel.getHeight();
    
    FontHandle* font = getTextFont();

    bool horizontal = true;
    if (m_parent != NULL)
    {
        horizontal = ((Tabs*)m_parent)->isHorizontal();
    }
    if (horizontal)
    {
        m_minSize.width += TAB_SIZE;
        if (m_closeable)
        {
            m_minSize.width += TAB_SIZE;
        }
        m_minSize.height += font->getPixelHeight();
        m_maxSize.set(maxTabSize, m_minSize.height);
    }
    else
    {
        m_minSize.height += TAB_SIZE;
        if (m_closeable)
        {
            m_minSize.height += TAB_SIZE;
        }
        m_minSize.width += font->getPixelHeight();
        m_maxSize.set(m_minSize.width, maxTabSize);
    }
    m_mouseDown = false;
}

void Tab::layout()
{
    // Our owning Tabs widget handles the content!
    m_mouseDown = false;
}

bool Tab::draw(Geek::Gfx::Surface* surface)
{
    BoxModel boxModel = getBoxModel();
    bool horizontal = true;
    int rotate = 0;

    Tabs* tabs = getTabs();
    if (tabs != NULL)
    {
        if (tabs->getTabPlacement() == TAB_LEFT)
        {
            rotate = 90;
            horizontal = false;
        }
        else if (tabs->getTabPlacement() == TAB_RIGHT)
        {
            rotate = 270;
            horizontal = false;
        }
    }

    drawBorder(surface);

    int titleWidth;
    if (horizontal)
    {
        titleWidth = m_setSize.width - boxModel.getWidth();
    }
    else
    {
        titleWidth = m_setSize.height - boxModel.getHeight();
    }


    int closeSize = 0;
    if (m_closeable)
    {
        if (horizontal)
        {
            closeSize = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
        }
        else
        {
            closeSize = m_app->getTheme()->getIconHeight();
        }
        titleWidth -= closeSize + 5;
    }

    int textOffsetX = boxModel.getLeft();
    int textOffsetY = boxModel.getTop();
    Size iconSize;
    if (m_icon != NULL)
    {
        iconSize = m_icon->getSize();
        int iconX = boxModel.getLeft();
        int iconY = boxModel.getTop();
        if (horizontal)
        {
            titleWidth -= iconSize.width + iconX;
            textOffsetX += iconSize.width + 2;;
            iconY = (m_setSize.height / 2) - (iconSize.height / 2);
        }
        else
        {
            titleWidth -= iconSize.height + iconY;
            textOffsetY += iconSize.height + 2;;
            iconX = (m_setSize.width / 2) - (iconSize.width / 2);
        }

        m_icon->draw(surface, iconX, iconY);
    }

    FontHandle* font = getTextFont();
    int labelHeight = font->getPixelHeight();

    if (horizontal)
    {
        textOffsetY = ((m_setSize.height / 2) - (labelHeight / 2));
    }
    else
    {
        textOffsetX = ((m_setSize.width / 2) - (labelHeight / 2));
    }

    int colour = getStyle("text-color").asInt();
    font->write(
        surface,
        textOffsetX,
        textOffsetY,
        getProperty(FRONTIER_PROP_TITLE).asString().c_str(),
        colour,
        true,
        NULL,
        titleWidth,
        rotate);

    if (m_closeable)
    {
        int closeX;
        int closeY;
        if (horizontal)
        {
            closeX = m_setSize.width - (closeSize + boxModel.getRight());
            closeY = ((m_setSize.height / 2) - (closeSize / 2));
        }
        else
        {
            closeX = ((m_setSize.width / 2) - (closeSize / 2));
            closeY = m_setSize.height - (closeSize + boxModel.getBottom());
        }

        m_app->getTheme()->drawIcon(
            surface,
            closeX,
            closeY,
            FRONTIER_ICON_WINDOW_CLOSE,
            false);
    }

    return true;
}

Widget* Tab::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        Tabs* tabs = getTabs();

        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        Vector2D thisPos = getAbsolutePosition();
        x -= thisPos.x;
        y -= thisPos.y;

        if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON)
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            if (m_closeable)
            {
                int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
                bool close = false;
                if (tabs == NULL || tabs->isHorizontal())
                {
                    close = (x > m_setSize.width - (closeWidth + 5));
                }
                else
                {
                    close = (y > m_setSize.height - (closeWidth + 5));
                }

                if (close)
                {
                    if (!mouseButtonEvent->direction && tabs != NULL)
                    {
                        tabs->closeTabSignal().emit(getContent());
                    }

                    return this;
                }
            }

            if (mouseButtonEvent->buttons == BUTTON_RIGHT)
            {
                log(DEBUG, "handleMessage: CONTEXT MENU!!!");
                openContextMenu(Geek::Vector2D(mouseButtonEvent->x, mouseButtonEvent->y));
            }
            else if (!mouseButtonEvent->direction)
            {
                m_mouseDown = false;
                return NULL;
            }
            else
            {
                m_mouseDown = true;
                m_mouseDownPos = Vector2D(mouseButtonEvent->x, mouseButtonEvent->y);
            }

            if (tabs != NULL)
            {
                tabs->setActiveTab(this);
            }

            return getContent();
        }
        else if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
        {
            MouseMotionEvent* mouseMotionEvent = (MouseMotionEvent*)event;
            if (m_mouseDown)
            {
                int diffX = abs((int)(mouseMotionEvent->x - m_mouseDownPos.x));
                int diffY = abs((int)(mouseMotionEvent->y - m_mouseDownPos.y));
                int diff = (int)sqrt((double)((diffX * diffX) + (diffY * diffY)));
                if (diff > 10)
                {
                    log(DEBUG, "Dragging tab!! diff=%d", diff);
                    m_mouseDown = false;
                    if (tabs != NULL)
                    {
                        tabs->closeTab(getContent(), false);
                    }
                    getWindow()->dragWidget(this);
                }
            }
        }
    }

    return this;
}

void Tab::add(Widget* content)
{
    Widget* existing = getContent();
    if (existing == content)
    {
        return;
    }

    if (existing != NULL)
    {
        existing->decRefCount();
        m_children.clear();
    }

    content->incRefCount();
    content->setParent(getParent());
    m_children.push_back(content);
}

Tabs* Tab::getTabs()
{
    if (m_parent != NULL && typeid(*m_parent) == typeid(Tabs))
    {
        return (Tabs*)m_parent;
    }
    return NULL;
}

void Tab::setTitle(wstring title)
{
    setProperty(FRONTIER_PROP_TITLE, Value(title));
    setDirty(DIRTY_CONTENT);
}

void Tab::setIcon(Icon* icon)
{
    m_icon = icon;
    setDirty(DIRTY_CONTENT);
}

