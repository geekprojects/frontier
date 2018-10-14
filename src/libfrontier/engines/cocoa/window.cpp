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


#include "cocoa_engine.h"

using namespace std;
using namespace Frontier;

CocoaWindow::CocoaWindow(FrontierWindow* window) : FrontierEngineWindow(window)
{
}

CocoaWindow::~CocoaWindow()
{
}


bool CocoaWindow::init()
{
    return createCocoaWindow();
}

bool CocoaWindow::update()
{
    Size winSize = m_window->getSize();
    //setSize(winSize);

#if 1
    Size currentSize = getSize();
    if (currentSize.width != winSize.width || currentSize.height != winSize.height)
    {
        setSize(winSize);
    }
#endif

    drawSurface(m_window->getSurface());

    return true;
}

