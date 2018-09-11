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
using namespace Geek::Gfx;

Button::Button(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_text = text;
    m_state = false;
}

Button::~Button()
{
}

void Button::calculateSize()
{
    m_minSize.width = m_ui->getTheme()->getTextWidth(m_text) + (5 * 2);
    m_minSize.height = m_ui->getTheme()->getTextHeight() + (5 * 2);

    m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    m_maxSize.height = m_minSize.height;
    //m_maxSize.height = WIDGET_SIZE_UNLIMITED;

    m_dirty = false;
}

bool Button::draw(Surface* surface)
{
    int w = m_ui->getTheme()->getTextWidth(m_text);
    int x = (m_setSize.width / 2) - (w / 2);

    int y = (m_setSize.height / 2) - (m_ui->getTheme()->getTextHeight() / 2);

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

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_BUTTON,
        state,
        0, 0,
        m_setSize.width, m_setSize.height);
    m_ui->getTheme()->drawText(surface, x, y, m_text);

    return true;
}

Widget* Button::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        switch (imsg->inputMessageType)
        {
            case FRONTIER_MSG_INPUT_MOUSE_BUTTON:
                printf("Button::handleMessage: Message! text=%ls\n", m_text.c_str());
                if (m_state != imsg->event.button.direction)
                {
                    setDirty();
                    m_state = imsg->event.button.direction;
                    if (!m_state)
                    {
                        UIMessage* buttonMessage = new UIMessage();
                        buttonMessage->messageType = FRONTIER_MSG_UI;
                        buttonMessage->uiMessageType = FRONTIER_MSG_UI_BUTTON_PRESSED;
                        buttonMessage->widget = this;
                        buttonMessage->source = msg;
                        buttonMessage->button.state = m_state;
                        m_ui->postMessage(buttonMessage);

                        m_clickSignal.emit();
                    }
                }
                break;

            default:
                break;
        }
    }
    return this;
}


