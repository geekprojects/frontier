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

#ifndef __FRONTIER_THEME_H_
#define __FRONTIER_THEME_H_

#include <geek/gfx-surface.h>

#include <frontier/fonts.h>

namespace Frontier
{

class FrontierApp;

enum UIBorderType
{
    BORDER_WIDGET,
    BORDER_BUTTON,
    BORDER_FRAME,
    BORDER_WINDOW,
    BORDER_SCROLLBAR,
    BORDER_SCROLLBAR_CONTROL,
    BORDER_LIST_BACKGROUND,
    BORDER_LIST_ITEM_1,
    BORDER_LIST_ITEM_2,
    BORDER_TAB,
    BORDER_INPUT,
};

enum UIState
{
    STATE_NONE,
    STATE_SELECTED,
    STATE_HOVER
};

enum ThemeColour
{
    COLOUR_WINDOW_BACKGROUND,
    COLOUR_WIDGET_BORDER_1,
    COLOUR_WIDGET_BORDER_2,
    COLOUR_WIDGET_GRADIENT_1,
    COLOUR_WIDGET_GRADIENT_2,

    COLOUR_SCROLLBAR_BACKGROUND,
    COLOUR_SCROLLBAR_CONTROL,

    COLOUR_LIST_ITEM_1,
    COLOUR_LIST_ITEM_2,
    COLOUR_LIST_ITEM_SELECTED,

    COLOUR_TAB_SELECTED_BACKGROUND,

    COLOUR_INPUT_BACKGROUND
};

class UITheme : public Geek::Logger
{
 protected:
    bool m_initialised;
    FontHandle* m_font;
    FontHandle* m_iconFont;
    FrontierApp* m_app;

    int m_margin;
    int m_padding;

 public:
    UITheme(FrontierApp* video);
    virtual ~UITheme();

    virtual bool init();

    virtual uint32_t getColour(ThemeColour colour);
    virtual int getMargin() const { return m_margin; }
    virtual int getPadding() const { return m_padding; }

    virtual void setMargin(int margin) { m_margin = margin; }
    virtual void setPadding(int padding) { m_padding = padding; }

    virtual void drawBackground(Geek::Gfx::Surface* surface);
    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state);
    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state, int x, int y, int w, int h);

    virtual void drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, int maxWidth = -1, bool inverted = false);
    virtual int getTextWidth(std::wstring text) const;
    virtual int getTextHeight() const;

    virtual void drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted = false);
    virtual int getIconWidth(wchar_t icon) const;
    virtual int getIconHeight() const;
    virtual FontHandle* getFont(bool highDPI) const;

    FrontierApp* getApp() const { return m_app; }
};

};

#endif
