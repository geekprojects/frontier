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
#include <frontier/widgets/label.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

FRONTIER_WIDGET(Label, Frontier::Label)

Label::Label(FrontierApp* ui) : Widget(ui, L"Label")
{
    m_align = ALIGN_CENTER;
    m_icon = NULL;
}

Label::Label(FrontierApp* ui, wstring widgetName, wstring text) : Widget(ui, widgetName)
{
    setProperty(FRONTIER_PROP_TEXT, Value(text));
    m_align = ALIGN_CENTER;
    m_icon = NULL;
}

Label::Label(FrontierApp* ui, wstring text) : Widget(ui, L"Label")
{
    setProperty(FRONTIER_PROP_TEXT, Value(text));
    m_align = ALIGN_CENTER;
    m_icon = NULL;
}

Label::Label(FrontierApp* ui, wstring text, HorizontalAlign align) : Widget(ui, L"Label")
{
    setProperty(FRONTIER_PROP_TEXT, Value(text));
    m_align = align;
    m_icon = NULL;
}

Label::Label(FrontierApp* ui, wstring text, Icon* icon) : Widget(ui, L"Label")
{
    setProperty(FRONTIER_PROP_TEXT, Value(text));
    m_align = ALIGN_CENTER;
    m_icon = icon;
}

Label::Label(FrontierApp* ui, wstring text, HorizontalAlign align, Icon* icon) : Widget(ui, L"Label")
{
    setProperty(FRONTIER_PROP_TEXT, Value(text));
    m_align = align;
    m_icon = NULL;
}

Label::~Label()
{
}

void Label::setText(std::wstring text)
{
    //if (text != m_text)
    {
        setProperty(FRONTIER_PROP_TEXT, Value(text));
        setDirty();
    }
}

void Label::setIcon(Icon* icon)
{
    m_icon = icon;
    setDirty(DIRTY_SIZE | DIRTY_CONTENT);
}

void Label::calculateSize()
{
    BoxModel boxModel = getBoxModel();
    FontHandle* font = getTextFont();
    m_lineHeight = font->getPixelHeight();

    m_minSize.set(0, 0);

    unsigned int pos = 0;
    int lines = 1;
    wstring line = L"";

    wstring text = getProperty(FRONTIER_PROP_TEXT).asString();

    for (pos = 0; pos < text.length(); pos++)
    {
        if (text[pos] == '\n' || pos == text.length() - 1)
        {
            if (pos == text.length() - 1)
            {
                line += text[pos];
            }
            else
            {
                lines++;
            }

            int w = font->width(line);
            if (w > m_minSize.width)
            {
                m_minSize.width = w;
            }
            line = L"";
        }
        else
        {
            line += text[pos];
        }
    }

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        if (m_minSize.width > 0)
        {
            m_minSize.width += boxModel.marginLeft;
        }
        m_minSize.width += iconSize.width;
        if (m_lineHeight < iconSize.height)
        {
            m_lineHeight = iconSize.height;
        }
    }

    m_minSize.width += boxModel.getWidth();
    m_minSize.height = (m_lineHeight * lines) + boxModel.getHeight();

    if (getStyle("expand-horizontal").asBool())
    {
        m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    }
    else
    {
        m_maxSize.width = m_minSize.width;
    }

    if (getStyle("expand-vertical").asBool())
    {
        m_maxSize.height = WIDGET_SIZE_UNLIMITED;
    }
    else
    {
        m_maxSize.height = m_minSize.height;
    }
}

bool Label::draw(Surface* surface)
{
    drawBorder(surface);

    BoxModel boxModel = getBoxModel();
    int y = boxModel.getTop();

    FontHandle* font = getTextFont();
    wstring text = getProperty(FRONTIER_PROP_TEXT).asString();

    int lines = 1;
    unsigned int pos = 0;
    for (pos = 0; pos < text.length(); pos++)
    {
        if (text[pos] == '\n')
        {
            lines++;
        }
    }

    y = (m_setSize.height / 2) - (lines * m_lineHeight) / 2;
 
    int maxX = 0;
    wstring line = L"";
    for (pos = 0; pos < text.length(); pos++)
    {
        if (text[pos] == '\n' || pos == text.length() - 1)
        {
            if (pos == text.length() - 1)
            {
                line += text[pos];
            }
            int w = font->width(line);
            int x = 0;

            if (m_icon != NULL)
            {
                Size iconSize = m_icon->getSize();
                w += iconSize.width;
            }

            switch (m_align)
            {
                case ALIGN_LEFT:
                    x = boxModel.getLeft();
                    break;
                case ALIGN_CENTER:
                    x = (m_setSize.width / 2) - (w / 2);
                    break;
                case ALIGN_RIGHT:
                    x = (m_setSize.width - boxModel.getRight()) - w;
                    break;
            }

            if (x + w > maxX)
            {
                maxX = x + w;
            }

            drawText(
                surface,
                x,
                y + 1,
                line.c_str(),
                font);
 
            y += m_lineHeight;
            line = L"";
        }
        else
        {
            line += text[pos];
        }
    }

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        int iconX;
        if (maxX > 0)
        {
            iconX = (maxX - iconSize.width) + (boxModel.marginLeft / 2);
        }
        else
        {
            iconX = boxModel.getLeft();
        }
        int iconY = (m_setSize.height / 2) - (iconSize.height / 2);
        m_icon->draw(surface, iconX, iconY);
    }

    return true;
}

