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

using namespace Frontier;

CocoaEngine::CocoaEngine(FrontierApp* app) : FrontierEngine(app)
{
}

CocoaEngine::~CocoaEngine()
{
}

bool CocoaEngine::init()
{
    bool res;

    res = createApplication();
    if (!res)
    {
        return false;
    }

    return true;
}

bool CocoaEngine::initWindow(FrontierWindow* window)
{

    bool res;

    CocoaWindow* cw = new CocoaWindow(window);

    res = cw->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(cw);
    return true;
}

bool CocoaEngine::checkEvents()
{
    return run();
}

