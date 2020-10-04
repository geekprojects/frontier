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


#include <frontier/widgets/colourbutton.h>
#include <frontier/fontawesome.h>

#include <math.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

FRONTIER_WIDGET(ColourButton, Frontier::ColourButton)

ColourButton::ColourButton(FrontierApp* app) : Button(app, L"ColourButton", L"")
{
    m_colour = Colour(255, 255, 255);

    setup();
}

ColourButton::ColourButton(FrontierApp* app, Geek::Gfx::Colour colour) : Button(app, L"ColourButton", L"")
{
    m_colour = colour;

    setup();
}

ColourButton::~ColourButton() = default;

void ColourButton::setup()
{
    m_colourIcon = getApp()->getTheme()->getIcon(FRONTIER_ICON_PALETTE);
    m_colourPicker = NULL;

    clickSignal().connect(sigc::mem_fun(*this, &ColourButton::onClick));
}

void ColourButton::calculateSize()
{
    BoxModel boxModel = getBoxModel();
    Size iconSize = m_colourIcon->getSize();

    m_minSize.width = boxModel.getWidth() + (iconSize.width * 3) + boxModel.marginLeft;
    m_minSize.height = boxModel.getHeight() + iconSize.height;

    m_maxSize.width = m_minSize.width;
    m_maxSize.height = m_minSize.height;
}

bool ColourButton::draw(Surface* surface)
{
    BoxModel boxModel = getBoxModel();
    drawBorder(surface);

    unsigned int colWidth = ((surface->getWidth() - (boxModel.getWidth() + boxModel.marginLeft)) / 3) * 2;
    unsigned int colHeight = (surface->getHeight() - boxModel.getHeight());

    surface->drawRectFilled(boxModel.getLeft(), boxModel.getTop(), colWidth, colHeight, m_colour.getInt32());

    m_colourIcon->draw(surface, (colWidth ) + boxModel.getLeft() + boxModel.marginLeft, boxModel.getTop());

    return true;
}

void ColourButton::onClick(Widget* widget)
{
    if (m_colourPicker != NULL)
    {
        m_colourPicker->show();
        return;
    }

    m_colourPicker = getApp()->openColourPickerWindow(m_colour);
    m_colourPicker->colourSelectedSignal().connect(sigc::mem_fun(*this, &ColourButton::setColour));
}

void ColourButton::setColour(Colour colour)
{
    m_colour = colour;
    setDirty(DIRTY_CONTENT);

    log(DEBUG, "setColour: colour: %s", colour.toHexString().c_str());
    m_colourSelectedSignal.emit(m_colour);

    getWindow()->requestUpdate();
}

