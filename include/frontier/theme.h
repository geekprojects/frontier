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
    BORDER_TAB
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

    COLOUR_TAB_SELECTED_BACKGROUND
};

class UITheme
{
 protected:
    bool m_initialised;
    FontHandle* m_font;
    FontHandle* m_fontHighDPI;
    FontHandle* m_iconFont;
    FontHandle* m_iconFontHighDPI;
    FrontierApp* m_app;

 public:
    UITheme(FrontierApp* video);
    virtual ~UITheme();

    virtual bool init();

    virtual uint32_t getColour(ThemeColour colour);

    virtual void drawBackground(Geek::Gfx::Surface* surface);
    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state);
    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state, int x, int y, int w, int h);

    virtual void drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, bool inverted = false);
    virtual int getTextWidth(std::wstring text);
    virtual int getTextHeight();

    virtual void drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted = false);
    virtual int getIconWidth(wchar_t icon);
    virtual int getIconHeight();

    FrontierApp* getApp() { return m_app; }
};

#define FRONTIER_ICON_FOLDER_OPEN 0xf07c
#define FRONTIER_ICON_CLOSE 0xf00d
#define FRONTIER_ICON_SAVE 0xf0c7
#define FRONTIER_ICON_SYNC 0xf021
#define FRONTIER_ICON_CARET_DOWN 0xf0d7
#define FRONTIER_ICON_CARET_UP 0xf0d8
#define FRONTIER_ICON_CARET_LEFT 0xf0d9
#define FRONTIER_ICON_CARET_RIGHT 0xf0da
#define FRONTIER_ICON_TREE 0xf1bb
#define FRONTIER_ICON_FILE 0xf15b
#define FRONTIER_ICON_FOLDER 0xf07b

};

#endif
