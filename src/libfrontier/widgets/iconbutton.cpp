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
#include <frontier/widgets/iconbutton.h>

using namespace std;
using namespace Frontier;
using namespace Geek::Gfx;

IconButton::IconButton(FrontierApp* ui, wchar_t icon) : Button(ui, L"")
{
    m_icon = icon;
    m_state = false;
}

IconButton::IconButton(FrontierWindow* window, wchar_t icon) : Button(window, L"")
{
    m_icon = icon;
    m_state = false;
}

IconButton::~IconButton()
{
}

void IconButton::calculateSize()
{
    m_minSize.width = m_app->getTheme()->getIconWidth(m_icon) + (5 * 2);
    m_minSize.height = m_app->getTheme()->getIconHeight() + (5 * 2);

    if (m_minSize.height > m_minSize.width)
    {
        m_minSize.width = m_minSize.height;
    }

    //    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
    m_maxSize = m_minSize;
}

bool IconButton::draw(Surface* surface)
{
    int w = m_app->getTheme()->getIconWidth(m_icon);
    int h = m_app->getTheme()->getIconHeight();
    int x = (m_setSize.width / 2) - (w / 2);
    int y = (m_setSize.height / 2) - (h / 2);

    if (m_state || m_mouseOver)
    {
        m_app->getTheme()->drawBorder(
            surface,
            BORDER_BUTTON,
            m_state ? STATE_SELECTED : STATE_HOVER,
            0, 0,
            m_setSize.width, m_setSize.height);
    }

    m_app->getTheme()->drawIcon(surface, x, y, m_icon);

    return true;
}

