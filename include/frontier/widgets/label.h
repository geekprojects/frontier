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

#ifndef __FRONTIER_WIDGETS_LABEL_H_
#define __FRONTIER_WIDGETS_LABEL_H_

#include <frontier/widgets.h>

#define FRONTIER_PROP_TEXT L"text"

namespace Frontier
{

/**
 * \brief Simple Widget for displaying text with optional Icon
 *
 * Other Widgets can inherit from Label to provide basic text formatting.
 *
 * \ingroup widgets
 *
 */
class Label : public Widget
{
 private:
    //std::wstring m_text;
    HorizontalAlign m_align;
    Icon* m_icon;

    int m_lineHeight;

 public:
    explicit Label(FrontierApp* ui);
    Label(FrontierApp* ui, std::wstring widgetName, std::wstring text);
    Label(FrontierApp* ui, std::wstring text);
    Label(FrontierApp* ui, std::wstring text, HorizontalAlign align);
    Label(FrontierApp* ui, std::wstring text, Icon* icon);
    Label(FrontierApp* ui, std::wstring text, HorizontalAlign align, Icon* icon);
    ~Label() override;

    void setText(std::wstring wtext);
    std::wstring getText() { return getProperty(FRONTIER_PROP_TEXT).asString(); }
    void setIcon(Icon* icon);
    Icon* getIcon() { return m_icon; }

    void calculateSize() override;
    bool draw(Geek::Gfx::Surface* surface) override;
};

}

#endif
