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
    Size borderSize = getBorderSize();
    int scrollbarWidth = getStyle("scrollbar-width");
    m_minSize = borderSize;
    m_minSize.width += scrollbarWidth;
    m_minSize.height += scrollbarWidth;

    m_maxSize.set(m_minSize.width, WIDGET_SIZE_UNLIMITED);
}

bool ScrollBar::draw(Surface* surface)
{
    BoxModel boxModel = getBoxModel();
    drawBorder(surface);

    int pos = getControlPos();
#if 0
    log(DEBUG, "draw: m_pos=%d, pos=%d", m_pos, pos);
#endif

    int sizePix = getControlSize();
#if 0
    log(DEBUG, "draw: sizePix=%d", sizePix);
#endif

    int drawWidth = getStyle("scrollbar-width");
    int x = (m_setSize.width / 2) - (drawWidth / 2);
    int y = boxModel.paddingTop + boxModel.marginTop;

    uint32_t controlColor = getStyle("scrollbar-color");
    surface->drawRectFilled(x, y + pos, drawWidth, sizePix, controlColor);

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

            BoxModel boxModel = getBoxModel();

            int y = mouseButtonEvent->y - thisPos.y;
            y -= (boxModel.getTop());

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

                BoxModel boxModel = getBoxModel();

                int yMax = (m_setSize.height - (boxModel.getHeight())) - getControlSize();

                float r = (float)(y - (boxModel.getTop())) / (float)(yMax);
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

    BoxModel boxModel = getBoxModel();
    int pos = (int)(((float)(m_pos) / (float)m_max) * (float)(m_setSize.height - boxModel.getHeight()));
    return pos;
}

int ScrollBar::getControlSize()
{
    if (m_max == 0)
    {
        return 0;
    }

    BoxModel boxModel = getBoxModel();

    //int range = m_max - (m_min + m_size);
    int sizePix = (int)(((float)m_size / (float)m_max) * (float)(m_setSize.height - boxModel.getHeight()));
    return sizePix;
}

