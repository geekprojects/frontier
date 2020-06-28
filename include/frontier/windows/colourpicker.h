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

#ifndef __FRONTIER_WINDOWS_COLOUR_PICKER_H_
#define __FRONTIER_WINDOWS_COLOUR_PICKER_H_

#include <frontier/window.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/hsvwheel.h>

namespace Frontier
{


/**
 * \brief Colour Picker Window
 *
 * Allows a user to select a colour
 *
 * \ingroup windows
 */
class ColourPickerWindow
{
 protected:
    Geek::Gfx::Colour m_colour;

    sigc::signal<void, Geek::Gfx::Colour> m_colourSelectedSignal;

 public:
    ColourPickerWindow(Geek::Gfx::Colour colour);
    virtual ~ColourPickerWindow();

    sigc::signal<void, Geek::Gfx::Colour> colourSelectedSignal() { return m_colourSelectedSignal; }

    virtual void show() {}
};

class FrontierColourPickerWindow : public ColourPickerWindow, public Frontier::FrontierWindow
{
 private:
    HSVWheel* m_hsvWheel;

    void onCloseButton(Widget* widget);
    void onHSVColourChange(Geek::Gfx::Colour);

 public:
    FrontierColourPickerWindow(Frontier::FrontierApp* app);
    FrontierColourPickerWindow(Frontier::FrontierApp* app, Geek::Gfx::Colour colour);
    virtual ~FrontierColourPickerWindow();

    bool init();
    bool update();
    void show();
};

};

#endif
