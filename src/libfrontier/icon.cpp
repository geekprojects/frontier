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


#include <frontier/icon.h>
#include <frontier/theme.h>

using namespace std;
using namespace Frontier;

Icon::Icon(UITheme* theme)
{
    m_theme = theme;
}

Icon::~Icon()
{
}

TextIcon::TextIcon(UITheme* theme, uint32_t icon) : Icon(theme)
{
    m_icon = icon;
}

TextIcon::~TextIcon()
{
}

Size TextIcon::getSize()
{
    Size size;
    size.width = m_theme->getIconWidth(m_icon);
    size.height = m_theme->getIconHeight();
    return size;
}

void TextIcon::draw(Geek::Gfx::Surface* surface, int x, int y)
{
    m_theme->drawIcon(surface, x, y, m_icon, false);
}

SurfaceIcon::SurfaceIcon(UITheme* theme, Geek::Gfx::Surface* surface) : Icon(theme)
{
    m_surface = surface;
    m_scaledSurface = NULL;
}

SurfaceIcon::~SurfaceIcon()
{
}

Size SurfaceIcon::getSize()
{
    Size size;
    //size.width = m_theme->getIconWidth(m_icon);
    size.width = m_theme->getIconHeight();
    size.height = m_theme->getIconHeight();
    return size;
}

void SurfaceIcon::draw(Geek::Gfx::Surface* surface, int x, int y)
{
if (m_scaledSurface == NULL)
{
    bool highDPI = surface->isHighDPI();
    Size size = getSize();
    if (highDPI)
    {
        size.width *= 2;
        size.height *= 2;
    }

    //if (m_surface->getWidth() != (uint32_t)size.width || m_surface->getHeight() != (uint32_t)size.height)
    {
        printf("SurfaceIcon::draw: Resizing to: %d, %d\n", size.width, size.height);
        m_scaledSurface = m_surface->scaleToFit(size.width, size.height);
    }
}

    surface->blit(x, y, m_scaledSurface, true);
}

