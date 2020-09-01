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
#include <frontier/widgets/textinput.h>

#include <wctype.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

FRONTIER_WIDGET(TextInput, Frontier::TextInput)

static wstring wchar2wstring(wchar_t c)
{
    wchar_t t[2];
    t[0] = c;
    t[1] = 0;
    return wstring(t);
}

TextInput::TextInput(FrontierApp* ui) : Widget(ui, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = 0;

    m_surfaceMutex = Thread::createMutex();

    setText(L"");
}

TextInput::TextInput(FrontierApp* ui, wstring text) : Widget(ui, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = 0;

    m_surfaceMutex = Thread::createMutex();

    setText(text);
}

TextInput::TextInput(FrontierWindow* window) : Widget(window, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = 0;

    m_surfaceMutex = Thread::createMutex();

    setText(L"");
}

TextInput::TextInput(FrontierWindow* window, wstring text) : Widget(window, L"TextInput")
{
    m_textSurface = NULL;
    m_maxLength = 0;

    m_surfaceMutex = Thread::createMutex();

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

    m_surfaceMutex->lock();
    if (m_textSurface != NULL)
    {
        delete m_textSurface;
        m_textSurface = NULL;
    }
    m_surfaceMutex->unlock();

    setDirty(DIRTY_CONTENT);
}

void TextInput::calculateSize()
{
    FontHandle* font = getTextFont();
    int lineHeight = font->getPixelHeight();

    Size borderSize = getBorderSize();

    m_minSize.set(50, lineHeight + borderSize.height);
    if (m_maxLength == 0)
    {
        m_maxSize.set(WIDGET_SIZE_UNLIMITED, lineHeight + borderSize.height);
    }
    else
    {
        int width = font->width(L"M");
        width *= m_maxLength;
        m_maxSize.set(width + borderSize.width, lineHeight + borderSize.height);
    }
}

bool TextInput::draw(Surface* surface)
{
    BoxModel boxModel = getBoxModel();

    FontHandle* font = getTextFont();

    drawBorder(surface);

    int lineHeight = font->getPixelHeight(72);
    unsigned int textWidth = getTextWidth(font, m_text) + 4;
    unsigned int textHeight = lineHeight + 2;

    int selectStart = MIN(m_selectStart, m_selectEnd);
    int selectEnd = MAX(m_selectStart, m_selectEnd);

    m_surfaceMutex->lock();
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

    if (hasStyle("background-color"))
    {
        uint32_t backgroundColour = getStyle("background-color").asInt();
        m_textSurface->clear(backgroundColour);
    }

    int x = 1;
    int y = 2;

    m_charX.clear();

    unsigned int cursorX = 0;
    unsigned int pos = 0;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        wstring cstr = wchar2wstring(m_text.at(pos));
        unsigned int width = font->width(cstr);

        if (hasSelection())
        {
            if ((int)pos >= selectStart && (int)pos < selectEnd)
            {
                m_textSurface->drawRectFilled(x, 0, width, textHeight, 0xffff0000);
            }
        }

        drawText(m_textSurface, x, y, cstr, font);

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

    drawCursor(m_textSurface, font, cursorX, y);

    m_surfaceMutex->unlock();

    unsigned int drawWidth = m_setSize.width - (boxModel.getWidth());
#if 0
    log(DEBUG, "draw: text=%ls, drawWidth=%d, textWidth=%d (%d), cursorX=%d", m_text.c_str(), drawWidth, textWidth, m_textSurface->getWidth(), cursorX);
#endif
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
    surface->blit(boxModel.getLeft(), boxModel.getTop(), m_textSurface, offsetX, 0, drawWidth, textHeight);

#if 0
    string filename = "text_";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        wchar_t c = m_text.at(pos);
        if (iswalnum(c))
        {
            filename += (char)c;
        }
    }
    filename += ".jpg";

    m_textSurface->saveJPEG(filename.c_str());
#endif

    return true;
}

void TextInput::drawCursor(Surface* surface, FontHandle* font, int x, int y)
{
    if (isActive())
    {
        int lineHeight = font->getPixelHeight(72);
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
                        m_signalTextChanged.emit(this);
                        break;

                    case KC_RETURN:
                        m_signalEditingEnd.emit(this);
                        break;

                    case KC_TAB:
                        m_signalEditingEnd.emit(this);
                        if (m_parent != NULL)
                        {
                            m_parent->activateNext(this);
                        }
                        break;

                    default:
                        if (iswprint(c))
                        {
                            wstring originalText = m_text;
                            if (hasSelection())
                            {
                                cutSelected();
                            }

                            m_text.insert(m_column, 1, c);
                            if (isValid(m_text))
                            {
                                m_column++;
                                m_signalTextChanged.emit(this);
                            }
                            else
                            {
                                m_text = originalText;
                            }
                        }
                        break;
                }
                setDirty(DIRTY_CONTENT);
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
        }

        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseMotionEvent* mouseMotionEvent = (MouseMotionEvent*)event;
            if (m_selecting)
            {
                setDirty(DIRTY_CONTENT);
                Vector2D pos = getAbsolutePosition();
                int x = mouseMotionEvent->x - pos.x;
                x -= m_offsetX;

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
#if 0
    log(DEBUG, "charAt: x=%d", x);
#endif
    int selected = -1;
    int i = 0;
    for (int charX : m_charX)
    {
#if 0
        log(DEBUG, "charAt: -> charX=%d", charX);
#endif
        if (x < charX)
        {
#if 0
            log(DEBUG, "charAt:   -> Gone beyond!");
#endif
            selected = i;
            break;
        }
        i++;
    }

#if 0
    log(DEBUG, "charAt: selected=%d", selected);
#endif

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

bool TextInput::isValid(std::wstring str)
{
    if (m_maxLength > 0)
    {
        return str.length() <= m_maxLength;
    }
    return true;
}

void TextInput::activateNext(Widget* activeChild)
{
    if (activeChild == NULL)
    {
        setActive();
    }
}

int TextInput::getTextWidth(FontHandle* font, wstring text)
{
    unsigned int pos = 0;
    int textWidth = 0;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        int cw = font->width(wchar2wstring(text.at(pos)));
        textWidth += cw;
    }
    return textWidth;
}

