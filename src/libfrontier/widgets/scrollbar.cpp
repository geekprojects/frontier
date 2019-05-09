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
#include <frontier/widgets/scrollbar.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define SCROLLBAR_BORDER 1

ScrollBar::ScrollBar(FrontierApp* ui) : Widget(ui, L"ScrollBar")
{
    m_pos = 0;
    m_size = 10;
    m_dragging = false;
    m_dragOffset = 0;
}

ScrollBar::ScrollBar(FrontierWindow* window) : Widget(window, L"ScrollBar")
{
    m_pos = 0;
    m_size = 10;
    m_dragging = false;
    m_dragOffset = 0;
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::calculateSize()
{
    m_minSize.set(10, 20);
    m_maxSize.set(10, WIDGET_SIZE_UNLIMITED);
}

bool ScrollBar::draw(Surface* surface)
{
    int drawWidth = m_setSize.width - (SCROLLBAR_BORDER * 2);

#if 0
    int drawHeight = m_setSize.height - (SCROLLBAR_BORDER * 2);
    log(DEBUG, "draw: drawWidth=%d, drawHeight=%d", drawWidth, drawHeight);
#endif

    //surface->drawRect(0, 0, m_setSize.width, m_setSize.height, 0xffffff);
    m_app->getTheme()->drawBorder(
        surface,
        BORDER_SCROLLBAR,
        STATE_NONE,
        0, 0,
        m_setSize.width, m_setSize.height);

    int pos = getControlPos();
#if 0
    log(DEBUG, "draw: m_pos=%d, pos=%d", m_pos, pos);
#endif

    int sizePix = getControlSize();
#if 0
    log(DEBUG, "draw: sizePix=%d", sizePix);
#endif

    m_app->getTheme()->drawBorder(
        surface,
        BORDER_SCROLLBAR_CONTROL,
        STATE_NONE,
        SCROLLBAR_BORDER, pos + SCROLLBAR_BORDER,
        drawWidth, sizePix);

    return true;
}

Widget* ScrollBar::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            FrontierWindow* window = getWindow();
            Vector2D thisPos = getAbsolutePosition();

            int pos = getControlPos();
            int sizePix = getControlSize();

            int y = mouseButtonEvent->y - thisPos.y;
            y -= SCROLLBAR_BORDER;

            if (mouseButtonEvent->direction)
            {
                if (y >= pos && y < pos + sizePix)
                {
                    m_dragging = true;
                    m_dragOffset = y - pos;
                    if (window != NULL)
                    {
                        window->setMotionWidget(this);
                    }
                }
            }
            else
            {
                m_dragging = false;
                if (window != NULL)
                {
                    window->setMotionWidget(NULL);
                }
            }
        } break;

        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseMotionEvent* mouseMotionEvent = (MouseMotionEvent*)event;
            if (m_dragging)
            {
                Vector2D thisPos = getAbsolutePosition();

                int range = m_max - (m_min + m_size);

                int y = mouseMotionEvent->y - thisPos.y;
                y -= m_dragOffset;

                int oldPos = m_pos;

                int yMax = (m_setSize.height - (SCROLLBAR_BORDER * 2)) - getControlSize();

                float r = (float)(y - SCROLLBAR_BORDER) / (float)(yMax);
                m_pos = (int)((float)range * r) + m_min;

                if (m_pos < m_min)
                {
                    m_pos = m_min;
                }
                else if (m_pos > (m_max - m_size))
                {
                    m_pos = m_max - m_size;
                }

                if (oldPos != m_pos)
                {
                    setDirty(DIRTY_CONTENT);
                    m_changedPositionSignal.emit(m_pos);
                }
            }
        } break;

        case FRONTIER_EVENT_MOUSE_SCROLL:
        {
            MouseScrollEvent* mouseScrollEvent = (MouseScrollEvent*)event;
            int scrollPos = getPos();
            scrollPos -= mouseScrollEvent->scrollY;
            setPos(scrollPos);
        } break;

        default:
            break;
    }

    return this;
}

void ScrollBar::set(int min, int max, int size)
{
    m_min = min;
    m_max = max;
    m_size = size;

    if (m_size > (m_max - m_min))
    {
        m_size = m_max - m_min;
        m_pos = 0;
    }
    if (m_pos > (m_max - m_size))
    {
        m_pos = m_max - m_size;
    }
    setDirty(DIRTY_CONTENT);
}

void ScrollBar::setPos(int pos)
{
    m_pos = pos;
    if (m_pos < m_min)
    {
        m_pos = m_min;
    }
    else if (m_pos > (m_max - m_size))
    {
        m_pos = m_max - m_size;
    }
    setDirty(DIRTY_CONTENT);
}

int ScrollBar::getPos()
{
    return m_pos;
}

int ScrollBar::getControlPos()
{
    if (m_max == 0)
    {
        return 0;
    }

    int pos = (int)(((float)(m_pos) / (float)m_max) * (float)(m_setSize.height - (SCROLLBAR_BORDER * 2)));
    return pos;
}

int ScrollBar::getControlSize()
{
    if (m_max == 0)
    {
        return 0;
    }

    //int range = m_max - (m_min + m_size);
    int sizePix = (int)(((float)m_size / (float)m_max) * (float)(m_setSize.height - (SCROLLBAR_BORDER * 2)));
    return sizePix;
}

