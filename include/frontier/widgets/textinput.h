/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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

#ifndef __FRONTIER_WIDGETS_INPUT_H_
#define __FRONTIER_WIDGETS_INPUT_H_

#include <frontier/widgets.h>

namespace Frontier
{

/**
 * \brief A Widget that allows a user to enter and edit text
 *
 * \ingroup widgets
 */
class TextInput : public Widget
{
 private:
    std::wstring m_text;
    unsigned int m_column;
    unsigned int m_offsetX;
    unsigned int m_maxLength;

    std::vector<int> m_charX;

    bool m_selecting;
    int m_selectStart;
    int m_selectEnd;

    void drawCursor(Geek::Gfx::Surface* surface, Geek::FontHandle* font, int x, int y);

    int charAt(int x);
    int getTextWidth(Geek::FontHandle* font, std::wstring text);

    Geek::Mutex* m_surfaceMutex;
    Geek::Gfx::Surface* m_textSurface;

    sigc::signal<void, TextInput*> m_signalEditingEnd;
    sigc::signal<void, TextInput*> m_signalTextChanged;

 public:
    TextInput(FrontierApp* ui);
    TextInput(FrontierApp* ui, std::wstring text);
    TextInput(FrontierWindow* ui);
    TextInput(FrontierWindow* ui, std::wstring text);
    virtual ~TextInput();

    void setMaxLength(unsigned int maxLen)
    {
        m_maxLength = maxLen;
    }

    void setText(std::wstring wtext);
    std::wstring getText() { return m_text; }

    bool hasSelection()
    {
        return (m_selectStart >= 0 && m_selectStart != m_selectEnd);
    }
    std::wstring getSelected();
    std::wstring cutSelected();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_EDIT; }

    virtual bool isValid(std::wstring str);

    sigc::signal<void, TextInput*> signalEditingEnd() { return m_signalEditingEnd; }
    sigc::signal<void, TextInput*> signalTextChanged() { return m_signalTextChanged; }
};

};

#endif
