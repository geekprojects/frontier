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
    int lineHeight = m_app->getTheme()->getTextHeight();

    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    m_minSize.width = 1 + m_app->getTheme()->getTextWidth(m_text);

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        //m_minSize.width += m_app->getTheme()->getIconWidth(m_icon);
        m_minSize.width += iconSize.width;
    }

    m_minSize.width += (getStyle(STYLE_MARGIN) * 2);
    m_minSize.height = lineHeight + (1 * 2);
}

bool TextListItem::draw(Geek::Gfx::Surface* surface)
{
    UIState state = STATE_NONE;
    if (m_selected)
    {
        state = STATE_SELECTED;
    }
    else if (m_mouseOver)
    {
        state = STATE_HOVER;
    }

    m_app->getTheme()->drawBorder(surface, BORDER_LIST_ITEM_1, state, 0, 0, surface->getWidth() - 2, surface->getHeight() - 2);

    int lineHeight = m_app->getTheme()->getTextHeight();
    int x = 1;
    int y = (surface->getHeight() / 2) - (lineHeight) / 2;

    if (m_icon != NULL)
    {
        Size iconSize = m_icon->getSize();
        int iconX = (ICON_WIDTH / 2) - (iconSize.width / 2);
        //m_app->getTheme()->drawIcon(surface, x + iconX, y, m_icon, m_selected);
        m_icon->draw(surface, x + iconX, y);
        x += ICON_WIDTH;
    }

    m_app->getTheme()->drawText(
        surface,
        x,
        y,
        m_text.c_str(),
        -1,
        m_selected);

    return true;
}

