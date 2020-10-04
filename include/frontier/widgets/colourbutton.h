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

#ifndef __FRONTIER_WIDGETS_COLOUR_BUTTON_H_
#define __FRONTIER_WIDGETS_COLOUR_BUTTON_H_

#include <frontier/widgets/button.h>
#include <frontier/windows/colourpicker.h>
#include <geek/gfx-colour.h>

namespace Frontier
{

class ColourButton : public Frontier::Button
{
 private:
    Icon* m_colourIcon;
    Geek::Gfx::Colour m_colour;
    ColourPickerWindow* m_colourPicker;

    sigc::signal<void, Geek::Gfx::Colour> m_colourSelectedSignal;

    void setup();

    void onClick(Widget* widget);

 public:
    explicit ColourButton(FrontierApp* app);
    ColourButton(FrontierApp* app, Geek::Gfx::Colour colour);
    ~ColourButton() override;

    void calculateSize() override;
    bool draw(Geek::Gfx::Surface* surface) override;

    void setColour(Geek::Gfx::Colour colour);

    sigc::signal<void, Geek::Gfx::Colour> colourSelectedSignal() { return m_colourSelectedSignal; }
};

}

#endif
