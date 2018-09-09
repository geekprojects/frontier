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

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

UITheme::UITheme(FrontierApp* app)
{
    m_app = app;
    m_initialised = false;

    m_font = NULL;
    m_iconFont = NULL;
}

bool UITheme::init()
{
    if (!m_initialised)
    {
        m_font = m_app->getFontManager()->openFont(
            "Helvetica Neue",
            FontStyle_Normal,
            12);
            m_initialised = true;

        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: Lato\n");
            return false;
        }
        m_fontHighDPI = m_app->getFontManager()->openFont(
            "Helvetica Neue",
            FontStyle_Normal,
            24);
            m_initialised = true;

        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: Lato\n");
            return false;
        }

        m_iconFont = m_app->getFontManager()->openFont(
            "FontAwesome",
            FontStyle_Normal,
            12);
            m_initialised = true;
        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: FontAwesome\n");
            return false;
        }

        m_iconFontHighDPI = m_app->getFontManager()->openFont(
            "FontAwesome",
            FontStyle_Normal,
            24);
            m_initialised = true;
        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: FontAwesome\n");
            return false;
        }

        m_initialised = true;
    }
    return true;
}

UITheme::~UITheme()
{
}

uint32_t UITheme::getColour(ThemeColour colour)
{
    switch (colour)
    {
        case COLOUR_WINDOW_BACKGROUND:
            return 0x003e3e3e;
        case COLOUR_BUTTON_1:
            return 0xff818181;
        case COLOUR_BUTTON_2:
            return 0xff0F0F0F;
        case COLOUR_WIDGET_GRADIENT_1:
            return 0xff616161;
        case COLOUR_WIDGET_GRADIENT_2:
            return 0xff434343;
        case COLOUR_SCROLLBAR_BACKGROUND:
            return 0x00000000;
        case COLOUR_SCROLLBAR_CONTROL:
            return 0xff818181;
        case COLOUR_LIST_ITEM_1:
            return 0xffcccccc;
        case COLOUR_LIST_ITEM_2:
            return 0xff888888;
        case COLOUR_LIST_ITEM_SELECTED:
            return 0xffffffff;
    }
}

void UITheme::drawBackground(Geek::Gfx::Surface* surface)
{
    surface->clear(getColour(COLOUR_WINDOW_BACKGROUND));
}

void UITheme::drawBorder(Surface* surface, UIBorderType type, UIState state, int x, int y, int width, int height)
{
    bool background = false;
    bool gradient = false;
    bool border = false;

    uint32_t b1 = getColour(COLOUR_BUTTON_1);
    uint32_t b2 = getColour(COLOUR_BUTTON_2);

    uint32_t g1 = getColour(COLOUR_WIDGET_GRADIENT_1);
    uint32_t g2 = getColour(COLOUR_WIDGET_GRADIENT_2);

    uint32_t backgroundColour = getColour(COLOUR_WINDOW_BACKGROUND);

    switch (type)
    {
        case BORDER_WIDGET:
        {
            border = true;
        } break;

        case BORDER_BUTTON:
        {
            border = true;
            gradient = true;
            if (state == STATE_SELECTED)
            {
                uint32_t tmp;

                tmp = b1;
                b1 = b2;
                b2 = tmp;
            }
        } break;

        case BORDER_SCROLLBAR:
        {
            background = true;
            backgroundColour = getColour(COLOUR_SCROLLBAR_BACKGROUND);
        } break;

        case BORDER_SCROLLBAR_CONTROL:
        {
            background = true;
            backgroundColour = getColour(COLOUR_SCROLLBAR_CONTROL);
        } break;

        case BORDER_LIST_ITEM_1:
        case BORDER_LIST_ITEM_2:
        {
background = true;
if (state == STATE_SELECTED)
{
backgroundColour = getColour(COLOUR_LIST_ITEM_SELECTED);
}
else if (type == BORDER_LIST_ITEM_1)
{
backgroundColour = getColour(COLOUR_LIST_ITEM_1);
}
else if (type == BORDER_LIST_ITEM_2)
{
backgroundColour = getColour(COLOUR_LIST_ITEM_1);
}
        } break;

        default:
            break;
    }

    if (gradient)
    {
        surface->drawGrad(x, y, width, height, g1, g2);
    }

if (background)
{
surface->drawRectFilled(x, y, width, height, backgroundColour);
}

if (border)
{
    surface->drawLine(x, y, x + width, y, b1);
    surface->drawLine(x, y, x, y + height, b1);

    surface->drawLine(x + width, y, x + width, y + height, b2);
    surface->drawLine(x, y + height, x + width, y + height, b2);
}
}

void UITheme::drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, bool inverted)
{
    uint32_t c = 0xffffffff;
    if (inverted)
    {
        c = 0xff000000;
    }

FontHandle* font = m_font;

    FontManager* fm = m_app->getFontManager();
    fm->write(font,
        surface,
        x,
        y,
        text.c_str(),
        c,
        true,
        NULL);
}

int UITheme::getTextWidth(std::wstring text)
{
    FontManager* fm = m_app->getFontManager();
    return fm->width(m_font, text.c_str());
}

int UITheme::getTextHeight()
{
    return m_font->getPixelHeight(72);
}

void UITheme::drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted)
{
    uint32_t c = 0xffffffff;
    if (inverted)
    {
        c = 0xff000000;
    }

    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    fm->write(m_iconFont,
        surface,
        x,
        y,
        text,
        c,
        true,
        NULL);
}

int UITheme::getIconWidth(wchar_t icon)
{
    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    return fm->width(m_iconFont, text);
}

int UITheme::getIconHeight()
{
    return m_iconFont->getPixelHeight(72);
}


