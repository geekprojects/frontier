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
}

Button::Button(FrontierWindow* window, wstring text) : Widget(window, L"Button")
{
    m_text = text;
}

Button::~Button()
{
}

void Button::calculateSize()
{
    FontHandle* font = getTextFont();

    m_minSize.width = font->getPixelWidth(m_text);
    m_minSize.height = font->getPixelHeight();

    Size borderSize = getBorderSize();
    m_minSize.width += borderSize.width;
    m_minSize.height += borderSize.height;

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = m_minSize.height;
}

bool Button::draw(Surface* surface)
{
    FontHandle* font = getTextFont();

    int w = font->getPixelWidth(m_text);
    int x = (m_setSize.width / 2) - (w / 2);
    int y = (m_setSize.height / 2) - (font->getPixelHeight() / 2);

    drawBorder(surface);

    drawText(surface, x, y, m_text, font);

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
            if (m_selected != mouseButtonEvent->direction)
            {
                setDirty(DIRTY_CONTENT | DIRTY_STYLE);

                m_selected = mouseButtonEvent->direction;

                if (!m_selected)
                {
                    m_clickSignal.emit(this);
                }
            }
        } break;

        case FRONTIER_EVENT_KEY:
        {
            KeyEvent* keyEvent = (KeyEvent*)event;
            if (keyEvent->direction && keyEvent->key == KC_TAB)
            {
                if (m_parent != NULL)
                {
                    m_parent->activateNext(this);
                }
            }
            else if (keyEvent->key == KC_SPACE)
            {
                if (m_selected != keyEvent->direction)
                {
                    setDirty(DIRTY_CONTENT | DIRTY_STYLE);

                    m_selected = keyEvent->direction;
                    if (!m_selected)
                    {
                        m_clickSignal.emit(this);
                    }
                }
            }
        } break;

        default:
            break;
    }
    return this;
}

void Button::activateNext(Widget* activeChild)
{
    if (activeChild == NULL)
    {
        setActive();
    }
}

