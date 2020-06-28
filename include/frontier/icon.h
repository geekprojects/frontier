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

#ifndef __FRONTIER_ICON_H_
#define __FRONTIER_ICON_H_

#include <stdint.h>
#include <frontier/object.h>
#include <frontier/fontawesome.h>
#include <frontier/utils.h>
#include <geek/gfx-surface.h>

namespace Frontier
{

class UITheme;

/**
 * \defgroup icons Graphical icons
 */

/**
 * \brief A base class for graphical icons
 *
 * \ingroup icons
 */
class Icon : public FrontierObject
{
 protected:
    UITheme* m_theme;
    
 public:
    Icon(UITheme* theme);
    virtual ~Icon();

    virtual Size getSize() = 0;
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y) = 0;
};

/**
 * \brief An Icon implemented with FontAwesome
 *
 * \ingroup icons
 */
class TextIcon : public Icon
{
 private:
    uint32_t m_icon;

 public:
    TextIcon(UITheme* theme, uint32_t icon);
    virtual ~TextIcon();

    virtual Size getSize();
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y);
};

/**
 * \brief An Icon implemented with a libgeek Surface
 *
 * \ingroup icons
 */
class SurfaceIcon : public Icon
{
 private:
    Geek::Gfx::Surface* m_surface;
    Geek::Gfx::Surface* m_scaledSurface;

 public:
    SurfaceIcon(UITheme* theme, Geek::Gfx::Surface* surface);
    virtual ~SurfaceIcon();

    virtual Size getSize();
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y);
};

};

#endif
