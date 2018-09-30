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

Label::Label(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_text = text;
    m_align = ALIGN_CENTER;
}

Label::Label(FrontierApp* ui, wstring text, TextAlign align) : Widget(ui)
{
    m_text = text;
    m_align = align;
}

Label::Label(FrontierWindow* window, wstring text) : Widget(window)
{
    m_text = text;
    m_align = ALIGN_CENTER;
}

Label::Label(FrontierWindow* window, wstring text, TextAlign align) : Widget(window)
{
    m_text = text;
    m_align = align;
}


Label::~Label()
{
}

void Label::setText(std::wstring text)
{
    m_text = text;
    setDirty();
}

void Label::setAlign(TextAlign align)
{
    m_align = align;
    setDirty();
}

void Label::calculateSize()
{
    m_lineHeight = m_ui->getTheme()->getTextHeight();

    m_minSize.set(0, 0);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    unsigned int pos = 0;
    int lines = 0;
    wstring line = L"";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n' || pos == m_text.length() - 1)
        {
            lines++;
            if (pos == m_text.length() - 1)
            {
                line += m_text[pos];
            }
            int w = m_ui->getTheme()->getTextWidth(line);
            if (w > m_minSize.width)
            {
                m_minSize.width = w;
            }
            line = L"";
        }
        else
        {
            line += m_text[pos];
        }
    }

    m_minSize.width += (m_margin * 2);
    m_minSize.height = (m_lineHeight * lines) + (m_margin * 2);

    m_maxSize.height = m_minSize.height;
}

bool Label::draw(Surface* surface)
{
    Widget::draw(surface);

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

    y = (m_setSize.height / 2) - (lines * m_lineHeight) / 2;
 
    wstring line = L"";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n' || pos == m_text.length() - 1)
        {
            if (pos == m_text.length() - 1)
            {
                line += m_text[pos];
            }
            int w = m_ui->getTheme()->getTextWidth(line);
            int x = 0;

            switch (m_align)
            {
                case ALIGN_LEFT:
                    x = m_margin;
                    break;
                case ALIGN_CENTER:
                    x = (m_setSize.width / 2) - (w / 2);
                    break;
                case ALIGN_RIGHT:
                    x = m_setSize.width - w;
                    break;
            }

            m_ui->getTheme()->drawText(
                surface,
                x,
                y,
                line.c_str());
 
            y += m_lineHeight;
            line = L"";
        }
        else
        {
            line += m_text[pos];
        }
    }

   return true;
}

Widget* Label::handleMessage(Message* msg)
{
    // We just swallow events
    return NULL;
}

