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

#define SCROLLBAR_BORDER 1

ScrollBar::ScrollBar(FrontierApp* ui) : Widget(ui)
{
    m_pos = 0;
    m_size = 10;
    m_dragging = false;
}

ScrollBar::ScrollBar(FrontierWindow* window) : Widget(window)
{
    m_pos = 0;
    m_size = 10;
    m_dragging = false;
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
    printf("ScrollBar::draw: drawWidth=%d, drawHeight=%d\n", drawWidth, drawHeight);
#endif

    //surface->drawRect(0, 0, m_setSize.width, m_setSize.height, 0xffffff);
    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_SCROLLBAR,
        STATE_NONE,
        0, 0,
        m_setSize.width, m_setSize.height);

    int pos = getControlPos();
#if 0
    printf("ScrollBar::draw: m_pos=%d, pos=%d\n", m_pos, pos);
#endif

    int sizePix = getControlSize();
    //printf("ScrollBar::draw: sizePix=%d\n", sizePix);

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_SCROLLBAR_CONTROL,
        STATE_NONE,
        SCROLLBAR_BORDER, pos + SCROLLBAR_BORDER,
        drawWidth, sizePix);

    return true;
}

Widget* ScrollBar::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            Vector2D thisPos = getAbsolutePosition();

            int pos = getControlPos();
            int sizePix = getControlSize();

            int y = imsg->event.button.y - thisPos.y;
            y -= SCROLLBAR_BORDER;

            if (imsg->event.button.direction)
            {
                if (y >= pos && y < pos + sizePix)
                {
//printf("ScrollBar::handleMessage: Control!!\n");
                    m_dragging = true;
                    if (imsg->window != NULL)
                    {
                        imsg->window->setDragWidget(this);
                    }
                }
            }
            else
            {
                m_dragging = false;
                if (imsg->window != NULL)
                {
                    imsg->window->setDragWidget(NULL);
                }
            }

/*
                setDirty(DIRTY_CONTENT);

                m_state = imsg->event.button.direction;
                UIMessage* buttonMessage = new UIMessage();
                buttonMessage->messageType = FRONTIER_MSG_UI;
                buttonMessage->uiMessageType = FRONTIER_MSG_UI_BUTTON_PRESSED;
                buttonMessage->widget = this;
                buttonMessage->source = msg;
                buttonMessage->button.state = m_state;
                m_ui->postMessage(buttonMessage);
*/
        }
        else if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
        {
            if (m_dragging)
            {
                Vector2D thisPos = getAbsolutePosition();

                int range = m_max - (m_min + m_size);

                int y = imsg->event.motion.y - thisPos.y;

                int oldPos = m_pos;

                float r = (float)(y - SCROLLBAR_BORDER) / (float)(m_setSize.height - (SCROLLBAR_BORDER * 2));
                m_pos = (int)((float)range * r) + m_min;

                if (m_pos < m_min)
                {
                    m_pos = m_min;
                }
                else if (m_pos > (m_max - m_size))
                {
                    m_pos = m_max - m_size;
                }
                //printf("ScrollBar::handleMessage: m_pos(2)=%d\n", m_pos);

                if (oldPos != m_pos)
                {
                    setDirty(DIRTY_CONTENT);
                    m_changedPositionSignal.emit(m_pos);
                }
            }
        }
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
    if (m_pos > (m_max - m_size))
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

