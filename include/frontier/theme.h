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

#ifndef __FRONTIER_THEME_H_
#define __FRONTIER_THEME_H_

#include <geek/gfx-surface.h>
#include <geek/fonts.h>

#include <frontier/icon.h>

#include <map>

namespace Frontier
{

class FrontierApp;

/**
 * \deprecated This should be merged in to FrontierApp
 */
class UITheme : public Geek::Logger
{
 protected:
    bool m_initialised;
    Geek::FontHandle* m_font;
    Geek::FontHandle* m_iconFont;
    Geek::FontHandle* m_monospaceFont;
    FrontierApp* m_app;

    std::map<uint32_t, Icon*> m_iconCache;

 public:
    UITheme(FrontierApp* video);
    virtual ~UITheme();

    virtual bool init();

    Icon* getIcon(uint32_t icon);

    virtual void drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted = false);
    virtual int getIconWidth(wchar_t icon) const;
    virtual int getIconHeight() const;
    virtual Geek::FontHandle* getFont(bool highDPI) const;
    virtual Geek::FontHandle* getIconFont(bool highDPI) const;

    virtual Geek::FontHandle* getMonospaceFont(bool highDPI) const;
    virtual int getMonospaceHeight() const;

    FrontierApp* getApp() const { return m_app; }
};

};

#endif
