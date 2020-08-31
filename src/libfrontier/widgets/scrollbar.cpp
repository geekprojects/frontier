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
#include <frontier/widgets/scrollbar.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

ScrollBar::ScrollBar(FrontierApp* ui, bool horizontal) : Widget(ui, L"ScrollBar")
{
    m_horizontal = horizontal;
    m_pos = 0;
    m_size = 10;
    m_dragging = false;
    m_dragOffset = 0;
}

ScrollBar::ScrollBar(FrontierWindow* window, bool horizontal) : Widget(window, L"ScrollBar")
{
    m_horizontal = horizontal;
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
    int scrollbarWidth = getStyle("scrollbar-width").asInt();
    m_minSize = borderSize;
    m_minSize.width += scrollbarWidth;
    m_minSize.height += scrollbarWidth;

    if (m_horizontal)
    {
        m_maxSize.set(WIDGET_SIZE_UNLIMITED, m_minSize.height);
    }
    else
    {
        m_maxSize.set(m_minSize.width, WIDGET_SIZE_UNLIMITED);
    }
}

bool ScrollBar::draw(Surface* surface)
{
    BoxModel boxModel = getBoxModel();
    drawBorder(surface);

    int pos = getControlPos(boxModel);
    int sizePix = getControlSize(boxModel);

    int drawSize = getStyle("scrollbar-width").asInt();
    uint32_t controlColor = getStyle("scrollbar-color").asInt();

    if (m_horizontal)
    {
        int x = boxModel.paddingLeft + boxModel.marginLeft;
        int y = (m_setSize.height / 2) - (drawSize / 2);
        surface->drawRectFilled(x + pos, y, sizePix, drawSize, controlColor);
    }
    else
    {
        int x = (m_setSize.width / 2) - (drawSize / 2);
        int y = boxModel.paddingTop + boxModel.marginTop;
        surface->drawRectFilled(x, y + pos, drawSize, sizePix, controlColor);
    }

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

            BoxModel boxModel = getBoxModel();
            int pos = getControlPos(boxModel);
            int sizePix = getControlSize(boxModel);

            int mousePos;
            if (m_horizontal)
            {
                mousePos = mouseButtonEvent->x - thisPos.x;
                mousePos -= (boxModel.getLeft());
            }
            else
            {
                mousePos = mouseButtonEvent->y - thisPos.y;
                mousePos -= (boxModel.getTop());
            }

            if (mouseButtonEvent->direction)
            {
                if (mousePos >= pos && mousePos < pos + sizePix)
                {
                    m_dragging = true;
                    m_dragOffset = mousePos - pos;
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
                BoxModel boxModel = getBoxModel();

                int oldPos = m_pos;

                int mousePos;
                int max;
                if (m_horizontal)
                {
                    mousePos = mouseMotionEvent->x - thisPos.x;
                    mousePos -= (boxModel.getLeft());
                    max = (m_setSize.width - (boxModel.getWidth())) - getControlSize(boxModel);
                }
                else
                {
                    mousePos = mouseMotionEvent->y - thisPos.y;
                    mousePos -= (boxModel.getTop());
                    max = (m_setSize.height - (boxModel.getHeight())) - getControlSize(boxModel);
                }

                mousePos -= m_dragOffset;
                float r = (float)(mousePos) / (float)(max);
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
            if (m_horizontal)
            {
                scrollPos -= mouseScrollEvent->scrollX;
            }
            else
            {
                scrollPos -= mouseScrollEvent->scrollY;
            }
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

int ScrollBar::getScaledValue(BoxModel& boxModel, int v)
{
    if (m_max == 0)
    {
        return 0;
    }

    int s;
    if (m_horizontal)
    {
        s = (int)(((float)(v) / (float)m_max) * (float)(m_setSize.width - boxModel.getWidth()));
    }
    else
    {
        s = (int)(((float)(v) / (float)m_max) * (float)(m_setSize.height - boxModel.getHeight()));
    }

    return s;
}

int ScrollBar::getControlPos(BoxModel& boxModel)
{
    return getScaledValue(boxModel, m_pos);
}

int ScrollBar::getControlSize(BoxModel& boxModel)
{
    return getScaledValue(boxModel, m_size);
}

