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
    m_textSurface = NULL;

    setText(L"");
}

TextInput::TextInput(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_textSurface = NULL;

    setText(text);
}

TextInput::TextInput(FrontierWindow* window) : Widget(window)
{
    m_textSurface = NULL;

    setText(L"");
}

TextInput::TextInput(FrontierWindow* window, wstring text) : Widget(window)
{
    m_textSurface = NULL;

    setText(text);
}

TextInput::~TextInput()
{
    if (m_textSurface != NULL)
    {
        delete m_textSurface;
    }
}

void TextInput::setText(std::wstring text)
{
    m_text = text;
    m_column = text.length();
    m_offsetX = 0;

    if (m_textSurface != NULL)
    {
        delete m_textSurface;
        m_textSurface = NULL;
    }

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

    unsigned int textWidth = m_ui->getTheme()->getTextWidth(m_text) + 4;
    unsigned int textHeight = lineHeight + 4;

    if (m_textSurface != NULL)
    {
        unsigned int surfaceWidth = m_textSurface->getWidth();
        if (m_textSurface->isHighDPI())
        {
            surfaceWidth /= 2;
        }
        if (surfaceWidth != textWidth)
        {
            delete m_textSurface;
            m_textSurface = NULL;
        }
    }

    if (m_textSurface == NULL)
    {
        if (surface->isHighDPI())
        {
            m_textSurface = new HighDPISurface(textWidth, textHeight, 4);
        }
        else
        {
            m_textSurface = new Surface(textWidth, textHeight, 4);
        }
    }

    m_textSurface->clear(m_ui->getTheme()->getColour(COLOUR_INPUT_BACKGROUND));
 
    int x = 2;//m_margin;
    int y = 2;//(m_setSize.height / 2) - (lineHeight / 2);

    unsigned int cursorX = 0;
    unsigned int pos = 0;
    wchar_t t[2];
    t[1] = 0;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        t[0] = m_text.at(pos);
        wstring cstr = wstring(t);

        int width = m_ui->getTheme()->getTextWidth(cstr);
        fm->write(font,
            m_textSurface,
            x,
            y,
            cstr,
            0xffffffff,
            true,
            NULL);

        if (pos == m_column)
        {
            cursorX = x;
        }

        x += width;
    }

    if (m_column == m_text.length())
    {
        cursorX = x;
    }

    drawCursor(m_textSurface, cursorX, y);

    unsigned int drawWidth = m_setSize.width - (m_margin * 2);
    if (drawWidth > textWidth)
    {
        m_offsetX = 0;
        drawWidth = textWidth;
    }
    else
    {
        unsigned int maxX = textWidth - drawWidth;
        if (m_offsetX > maxX)
        {
            m_offsetX = maxX;
        }

        if (cursorX < m_offsetX)
        {
            m_offsetX = cursorX;
        }
        else if (cursorX >= m_offsetX + drawWidth)
        {
            m_offsetX = (cursorX - drawWidth) + 1;
        }
    }

    unsigned int offsetX = m_offsetX;
    if (m_textSurface->isHighDPI())
    {
        offsetX *= 2;
        drawWidth *= 2;
        textHeight *= 2;
    }
    surface->blit(m_margin, m_margin, m_textSurface, offsetX, 0, drawWidth, textHeight);

   return true;
}

void TextInput::drawCursor(Surface* surface, int x, int y)
{
    if (isActive())
    {
        int lineHeight = m_ui->getTheme()->getTextHeight();
        surface->drawLine(x, y - 1, x, y + lineHeight, 0xffffffff);
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

