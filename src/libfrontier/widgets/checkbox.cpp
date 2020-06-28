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
#include <frontier/widgets/checkbox.h>

using namespace std;
using namespace Frontier;
using namespace Geek::Gfx;

CheckBox::CheckBox(FrontierApp* ui) : Button(ui, L"CheckBox", L"", BUTTON_TOGGLE)
{
    m_icon = getApp()->getTheme()->getIcon(FRONTIER_ICON_CHECK);
}

CheckBox::~CheckBox()
{
}

void CheckBox::calculateSize()
{
    m_minSize = m_icon->getSize();

    Size borderSize = getBorderSize();
    m_minSize.width += borderSize.width;
    m_minSize.height += borderSize.height;

    if (m_minSize.height > m_minSize.width)
    {
        m_minSize.width = m_minSize.height;
    }

    m_maxSize = m_minSize;
}

bool CheckBox::draw(Surface* surface)
{
    Size iconSize = m_icon->getSize();
    int x = (m_setSize.width / 2) - (iconSize.width / 2);
    int y = (m_setSize.height / 2) - (iconSize.height / 2);

    drawBorder(surface);

    if (m_selected)
    {
        m_icon->draw(surface, x, y);
    }

    return true;
}

