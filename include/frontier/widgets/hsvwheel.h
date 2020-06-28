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

#ifndef __FRONTIER_WIDGETS_HSV_WHEEL_H_
#define __FRONTIER_WIDGETS_HSV_WHEEL_H_

#include <frontier/widgets.h>
#include <geek/gfx-colour.h>

namespace Frontier
{

/**
 * \brief Displays an HSV colour wheel allowing the user to select colours
 *
 * \ingroup widgets
 */
class HSVWheel : public Widget
{
 private:
    double m_brightness;
    Geek::Gfx::Colour m_colour;

    sigc::signal<void, Geek::Gfx::Colour> m_signalColourChanged;

    bool hsvFromPosition(double* hsv, int x, int y, int cx, int cy, int radius);
    void updateFromMouse(MouseEvent* mouseEvent);

 public:
    HSVWheel(Frontier::FrontierApp* app);
    HSVWheel(Frontier::FrontierApp* app, Geek::Gfx::Colour colour);
    virtual ~HSVWheel();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    sigc::signal<void, Geek::Gfx::Colour> signalColourChanged() { return m_signalColourChanged; };
};

};

#endif
