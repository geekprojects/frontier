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
#include <frontier/widgets/textinput.h>

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek::Gfx;

TextInput::TextInput(FrontierApp* ui) : Widget(ui)
{
    m_text = L"";
    m_column = 0;
}

TextInput::TextInput(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_text = text;
    m_column = text.length();
}

TextInput::TextInput(FrontierWindow* window) : Widget(window)
{
    m_text = L"";
    m_column = 0;
}

TextInput::TextInput(FrontierWindow* window, wstring text) : Widget(window)
{
    m_text = text;
    m_column = text.length();
}

TextInput::~TextInput()
{
}

void TextInput::setText(std::wstring text)
{
    m_text = text;
    m_column = text.length();
    setDirty();
}

void TextInput::calculateSize()
{
    int lineHeight = m_ui->getTheme()->getTextHeight();

    m_minSize.set(50, lineHeight + (m_margin * 2));
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, lineHeight + (m_margin * 2));
}

bool TextInput::draw(Surface* surface)
{
    int lineHeight = m_ui->getTheme()->getTextHeight();

    FontManager* fm = m_ui->getFontManager();
    FontHandle* font = m_ui->getTheme()->getFont(surface->isHighDPI());

    UIState state = STATE_NONE;
    if (isActive())
    {
        state = STATE_SELECTED;
    }

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_INPUT,
        state,
        0, 0,
        m_setSize.width, m_setSize.height);

    int y = m_margin;

    int lines = 1;
    unsigned int pos = 0;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n')
        {
            lines++;
        }
    }

    y = (m_setSize.height / 2) - (lines * lineHeight) / 2;
 
    wstring line = L"";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n' || pos == m_text.length() - 1)
        {
            if (pos == m_text.length() - 1)
            {
                line += m_text[pos];
            }
            //int w = m_ui->getTheme()->getTextWidth(line);
            int x = m_margin;

            unsigned int i;
            for (i = 0; i < line.length(); i++)
            {
                wstring cstr = wstring(L"") + line.at(i);


                int width = m_ui->getTheme()->getTextWidth(cstr);
                fm->write(font,
                    surface,
                    x,
                    y,
                    cstr,
                    0xffffffff,
                    true,
                    NULL);

                if (i == m_column)
                {
                    drawCursor(surface, x, y);
                }
 
                x += width;
            }

            if (m_column == line.length())
            {
                drawCursor(surface, x, y);
            }

            y += lineHeight;
            line = L"";
        }
        else
        {
            line += m_text[pos];
        }
    }

    if (m_text.length() == 0)
    {
        drawCursor(surface, m_margin, y);
    }

   return true;
}

void TextInput::drawCursor(Surface* surface, int x, int y)
{
    if (isActive())
    {
        int lineHeight = m_ui->getTheme()->getTextHeight();
        surface->drawLine(x, y - 1, x, y + lineHeight + 1, 0xffffffff);
    }
}

Widget* TextInput::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* inputMessage = (InputMessage*)msg;
        switch (inputMessage->inputMessageType)
        {
            case FRONTIER_MSG_INPUT_KEY:
            {
                if (inputMessage->event.key.direction)
                {
                    wchar_t c = L'?';
                    if (iswprint(inputMessage->event.key.chr))
                    {
                        c = inputMessage->event.key.chr;
                    }

                    printf("Input::handleMessage: Key press: 0x%x (%d) -> %lc, modifiers=0x%x\n",
                        inputMessage->event.key.key,
                        inputMessage->event.key.key,
                        c,
                        inputMessage->event.key.modifiers);

                    switch (inputMessage->event.key.key)
                    {
                        case KC_LEFT:
                            if (m_column > 0)
                            {
                                m_column--;
                            }
                            break;
                        case KC_RIGHT:
                            if (m_column < m_text.length())
                            {
                                m_column++;
                            }
                            break;
                        case KC_BACKSPACE:
                            if (m_column > 0)
                            {
                                m_column--;
                                m_text.erase(m_column, 1);
                            }
                            break;
                        default:
                            if (iswprint(c))
                            {
                                m_text.insert(m_column, 1, c);
                                m_column++;
                            }
                    }
                    setDirty();
                }
                return this;
            } break;

            case FRONTIER_MSG_INPUT_MOUSE_BUTTON:
                setDirty(DIRTY_CONTENT);
                return this;

            case FRONTIER_MSG_INPUT_MOUSE_MOTION:
                return this;

            default:
                break;
        }
    }
    return NULL;
}

