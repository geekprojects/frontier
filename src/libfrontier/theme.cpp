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

UITheme::UITheme(FrontierApp* app) : Logger("UITheme")
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
        m_initialised = true;

        m_font = m_app->getFontManager()->openFont(
            "System Font",
            "Regular",
            12);
        if (m_font == NULL)
        {
            m_font = m_app->getFontManager()->openFont(
                "Lato",
                "Regular",
                12);
            if (m_font == NULL)
            {
                log(ERROR, "init: Failed to find UI font");
                return false;
            }
        }

        m_iconFont = m_app->getFontManager()->openFont(
            "Font Awesome 5 Free",
            "Solid",
            12);
        if (m_iconFont == NULL)
        {
            log(ERROR, "init: Failed to find FontAwesome");
            return false;
        }

        m_monospaceFont = m_app->getFontManager()->openFont(
            "Hack",
            "Regular",
            10);
        if (m_monospaceFont == NULL)
        {
            log(ERROR, "init: Failed to find Hack font");
            return false;
        }
    }
    return true;
}

UITheme::~UITheme()
{
    map<uint32_t, Icon*>::iterator it;
    for (it = m_iconCache.begin(); it != m_iconCache.end(); it++)
    {
        (it->second)->decRefCount();
    }
}

Icon* UITheme::getIcon(uint32_t iconId)
{
    map<uint32_t, Icon*>::iterator it;
    it = m_iconCache.find(iconId);
    if (it != m_iconCache.end())
    {
        return it->second;
    }


    Icon* icon = new TextIcon(this, iconId);
    icon->incRefCount();
    m_app->registerObject(icon);
    m_iconCache.insert(make_pair(iconId, icon));

    return icon;
}

void UITheme::drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted)
{
    uint32_t c = 0xffffffff;
    if (inverted)
    {
        c = 0xff000000;//getColour(COLOUR_WINDOW_BACKGROUND);;
    }

    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    fm->write(m_iconFont,
        surface,
        x,
        y + 2, // These extra pixels seem to be required for Font Awesome
        text,
        c,
        true,
        NULL);
}

int UITheme::getIconWidth(wchar_t icon) const
{
    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    return fm->width(m_iconFont, text);
}

int UITheme::getIconHeight() const
{
    return m_iconFont->getPixelHeight(72);
}

FontHandle* UITheme::getFont(bool highDPI) const
{
    return m_font;
}

FontHandle* UITheme::getIconFont(bool highDPI) const
{
    return m_iconFont;
}

FontHandle* UITheme::getMonospaceFont(bool highDPI) const
{
    return m_monospaceFont;
}

int UITheme::getMonospaceHeight() const
{
    return m_monospaceFont->getPixelHeight(72);
}

