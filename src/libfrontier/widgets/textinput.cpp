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
using namespace Geek;
using namespace Geek::Gfx;

TextInput::TextInput(FrontierApp* ui) : Widget(ui, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = -1;

    setText(L"");
}

TextInput::TextInput(FrontierApp* ui, wstring text) : Widget(ui, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = -1;

    setText(text);
}

TextInput::TextInput(FrontierWindow* window) : Widget(window, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = -1;

    setText(L"");
}

TextInput::TextInput(FrontierWindow* window, wstring text) : Widget(window, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = -1;

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

    m_selecting = false;
    m_selectStart = -1;
    m_selectEnd = -1;

    if (m_textSurface != NULL)
    {
        delete m_textSurface;
        m_textSurface = NULL;
    }

    setDirty();
}

void TextInput::calculateSize()
{
    int lineHeight = m_app->getTheme()->getTextHeight();

    m_minSize.set(50, lineHeight + (m_margin * 2));
if (m_maxLength == -1)
{
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, lineHeight + (m_margin * 2));
}
else
{
int width = m_app->getTheme()->getTextWidth(L"M");
width *= m_maxLength;
    m_maxSize.set(width + (m_margin * 2), lineHeight + (m_margin * 2));
}
}

bool TextInput::draw(Surface* surface)
{
    int lineHeight = m_app->getTheme()->getTextHeight();

    FontManager* fm = m_app->getFontManager();
    FontHandle* font = m_app->getTheme()->getFont(surface->isHighDPI());

    UIState state = STATE_NONE;
    if (isActive())
    {
        state = STATE_SELECTED;
    }

    m_app->getTheme()->drawBorder(
        surface,
        BORDER_INPUT,
        state,
        0, 0,
        m_setSize.width, m_setSize.height);

    unsigned int textWidth = m_app->getTheme()->getTextWidth(m_text) + 4;
    unsigned int textHeight = lineHeight + 4;

    int selectStart = MIN(m_selectStart, m_selectEnd);
    int selectEnd = MAX(m_selectStart, m_selectEnd);

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

    m_textSurface->clear(m_app->getTheme()->getColour(COLOUR_INPUT_BACKGROUND));
 
    int x = 2;
    int y = 2;

    m_charX.clear();

    unsigned int cursorX = 0;
    unsigned int pos = 0;
    wchar_t t[2];
    t[1] = 0;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        t[0] = m_text.at(pos);
        wstring cstr = wstring(t);

        int width = m_app->getTheme()->getTextWidth(cstr);

        if (hasSelection())
        {
            if ((int)pos >= selectStart && (int)pos < selectEnd)
            {
                m_textSurface->drawRectFilled(x, 0, width, textHeight, 0xffff0000);
            }
        }

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
        m_charX.push_back(x);
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
        int lineHeight = m_app->getTheme()->getTextHeight();
        surface->drawLine(x, y - 1, x, y + lineHeight, 0xffffffff);
    }
}

Widget* TextInput::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_KEY:
        {
            KeyEvent* keyEvent = (KeyEvent*)event;

            if (keyEvent->direction)
            {
                wchar_t c = L'?';
                if (iswprint(keyEvent->chr))
                {
                    c = keyEvent->chr;
                }

                log(DEBUG, "handleMessage: Key press: 0x%x (%d) -> %lc, modifiers=0x%x",
                    keyEvent->key,
                    keyEvent->key,
                    c,
                    keyEvent->modifiers);

                switch (keyEvent->key)
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
                        if (hasSelection())
                        {
                            cutSelected();
                        }
                        else if (m_column > 0)
                        {
                            m_column--;
                            m_text.erase(m_column, 1);
                        }
                        break;

                    case KC_RETURN:
                        m_signalTextEnter.emit(this);
                        break;

                    default:
                        if (iswprint(c))
                        {
                            if (hasSelection())
                            {
                                cutSelected();
                            }
                            m_text.insert(m_column, 1, c);
                            m_column++;
                        }
                }
                setDirty();
            }
            return this;
        }

        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            setDirty(DIRTY_CONTENT);

            Vector2D pos = getAbsolutePosition();
            int x = mouseButtonEvent->x - pos.x;
            x -= m_offsetX;
            log(DEBUG, "handleMessage: FRONTIER_EVENT_MOUSE_BUTTON: x=%d", x);

            int at = charAt(x);
            if (mouseButtonEvent->direction)
            {
                m_selecting = true;
                m_selectStart = at;
                m_selectEnd = at;
                m_column = at;
            }
            else
            {
                m_selecting = false;
            }

            return this;
        } break;

        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseMotionEvent* mouseMotionEvent = (MouseMotionEvent*)event;
            if (m_selecting)
            {
                setDirty(DIRTY_CONTENT);
                Vector2D pos = getAbsolutePosition();
                int x = mouseMotionEvent->x - pos.x;
                x -= m_offsetX;
                log(DEBUG, "handleMessage: FRONTIER_EVENT_MOUSE_MOTION: x=%d", x);

                int at = charAt(x);

                m_selectEnd = at;
                m_column = at;
            }

            return this;
        }

        default:
            break;
    }
    return NULL;
}

int TextInput::charAt(int x)
{
    log(DEBUG, "charAt: x=%d", x);
    int selected = -1;
    int i = 0;
    for (int charX : m_charX)
    {
        log(DEBUG, "charAt: -> charX=%d", charX);
        if (x < charX)
        {
            log(DEBUG, "charAt:   -> Gone beyond!");
            selected = i;
            break;
        }
        i++;
    }

    log(DEBUG, "charAt: selected=%d", selected);

    if (selected >= 0)
    {
        return selected;
    }
    else
    {
        return m_text.length();
    }
}

wstring TextInput::getSelected()
{
    if (hasSelection())
    {
        int selectStart = MIN(m_selectStart, m_selectEnd);
        int selectEnd = MAX(m_selectStart, m_selectEnd);
        int selectLen = selectEnd - selectStart;

        return m_text.substr(selectStart, selectLen);
    }
    return L"";
}

wstring TextInput::cutSelected()
{
    if (hasSelection())
    {
        int selectStart = MIN(m_selectStart, m_selectEnd);
        int selectEnd = MAX(m_selectStart, m_selectEnd);
        int selectLen = selectEnd - selectStart;

        wstring selectText = m_text.substr(selectStart, selectLen);

        m_text.erase(selectStart, selectLen);

        m_column = selectStart;
        m_selectStart = -1;
        return selectText;
    }
    return L"";
}

