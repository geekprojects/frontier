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


#include <frontier/windows/colourpicker.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/label.h>
#include <frontier/fontawesome.h>

using namespace Geek;
using namespace Geek::Gfx;
using namespace Frontier;
using namespace std;

ColourPickerWindow::ColourPickerWindow(Colour colour)
{
    m_colour = colour;
}


ColourPickerWindow::~ColourPickerWindow()
{
}

FrontierColourPickerWindow::FrontierColourPickerWindow(Frontier::FrontierApp* app)
    : ColourPickerWindow(Colour(255, 255, 255)), FrontierWindow(app, L"Colour Picker", WINDOW_NORMAL)
{
}

FrontierColourPickerWindow::FrontierColourPickerWindow(Frontier::FrontierApp* app, Colour colour)
    : ColourPickerWindow(colour), FrontierWindow(app, L"Colour Picker", WINDOW_NORMAL)
{
}


FrontierColourPickerWindow::~FrontierColourPickerWindow()
{
    log(DEBUG, "~ColourPickerWindow: Deleting!");
}

bool FrontierColourPickerWindow::init()
{
    setSize(Size(100, 100));

    Frame* root = new Frame(this, false);
    root->setWidgetClass(L"colourPicker");

    m_hsvWheel = new HSVWheel(getApp(), m_colour);
    m_hsvWheel->signalColourChanged().connect(sigc::mem_fun(*this, &FrontierColourPickerWindow::onHSVColourChange));
    root->add(m_hsvWheel);

    Button* closeButton = new Button(getApp(), L"Close");
    closeButton->clickSignal().connect(sigc::mem_fun(*this, &FrontierColourPickerWindow::onCloseButton));
    root->add(closeButton);

    setContent(root);

    update();

    return true;
}

bool FrontierColourPickerWindow::update()
{
    return true;
}

void FrontierColourPickerWindow::show()
{
    FrontierWindow::show();
}

void FrontierColourPickerWindow::onCloseButton(Widget* widget)
{
    hide();
}

void FrontierColourPickerWindow::onHSVColourChange(Geek::Gfx::Colour colour)
{
log(DEBUG, "onHSVColourChange: Here!!");
    m_colourSelectedSignal.emit(colour);
}

