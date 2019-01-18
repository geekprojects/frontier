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
#include <frontier/widgets/button.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Button::Button(FrontierApp* ui, wstring text) : Widget(ui, L"Button")
{
    m_text = text;
    m_state = false;
}

Button::Button(FrontierWindow* window, wstring text) : Widget(window, L"Button")
{
    m_text = text;
    m_state = false;
}

Button::~Button()
{
}

void Button::calculateSize()
{
    m_minSize.width = m_app->getTheme()->getTextWidth(m_text) + (5 * 2);
    m_minSize.height = m_app->getTheme()->getTextHeight() + (5 * 2);

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = m_minSize.height;
    //m_maxSize.height = WIDGET_SIZE_UNLIMITED;
}

bool Button::draw(Surface* surface)
{
    int w = m_app->getTheme()->getTextWidth(m_text);
    int x = (m_setSize.width / 2) - (w / 2);

    int y = (m_setSize.height / 2) - (m_app->getTheme()->getTextHeight() / 2);

    UIState state;
    if (m_state)
    {
        state = STATE_SELECTED;
    }
    else if (m_mouseOver)
    {
        state = STATE_HOVER;
    }
    else
    {
        state = STATE_NONE;
    }

    m_app->getTheme()->drawBorder(
        surface,
        BORDER_BUTTON,
        state,
        0, 0,
        m_setSize.width, m_setSize.height);
    m_app->getTheme()->drawText(surface, x, y, m_text);

    return true;
}

Widget* Button::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            log(DEBUG, "handleEvent: Message! text=%ls", m_text.c_str());
            if (m_state != mouseButtonEvent->direction)
            {
                setDirty(DIRTY_CONTENT);

                m_state = mouseButtonEvent->direction;
                if (!m_state)
                {
                    m_clickSignal.emit();
                }
            }
        } break;

        default:
            break;
    }
    return this;
}


