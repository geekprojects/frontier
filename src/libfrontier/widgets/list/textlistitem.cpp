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
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define ICON_WIDTH 20

TextListItem::TextListItem(FrontierApp* ui, std::wstring text) : ListItem(ui)
{
    m_icon = NULL;
    m_text = text;
}

TextListItem::TextListItem(FrontierApp* ui, Icon* icon, std::wstring text) : ListItem(ui)
{
    m_icon = icon;
    m_text = text;
}

TextListItem::TextListItem(FrontierWindow* window, std::wstring text) : ListItem(window)
{
    m_icon = NULL;
    m_text = text;
}

TextListItem::TextListItem(FrontierWindow* window, Icon* icon, std::wstring text) : ListItem(window)
{
    m_icon = icon;
    m_text = text;
}

TextListItem::~TextListItem()
{
}

void TextListItem::setText(std::wstring text)
{
    m_text = text;
    setDirty();
}

void TextListItem::calculateSize()
{
    BoxModel boxModel = getBoxModel();

    FontHandle* font = getTextFont();
    if (font == NULL)
    {
        return;
    }
    int lineHeight = font->getPixelHeight();

    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_minSize.width = 1 + font->width(m_text);

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        m_minSize.width += iconSize.width;
    }
    m_minSize.height = lineHeight;

    m_minSize.width += boxModel.getWidth();
    m_minSize.height += boxModel.getHeight();
}

bool TextListItem::draw(Geek::Gfx::Surface* surface)
{
    drawBorder(surface);

    FontHandle* font = getTextFont();
    if (font == NULL)
    {
        return false;
    }

    int lineHeight = font->getPixelHeight();
    int x = 1;
    int y = (surface->getHeight() / 2) - (lineHeight) / 2;

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        int iconX = (ICON_WIDTH / 2) - (iconSize.width / 2);
        m_icon->draw(surface, x + iconX, y);
        x += ICON_WIDTH;
    }

    drawText(surface, x, y, m_text);

    return true;
}

