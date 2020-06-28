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


#include <frontier/engines/embedded.h>

using namespace std;
using namespace Frontier;

EmbeddedEngine::EmbeddedEngine(FrontierApp* app) : FrontierEngine(app)
{
    m_scaleFactor = 1.0;
}

EmbeddedEngine::~EmbeddedEngine()
{
}

bool EmbeddedEngine::init()
{
    return true;
}

bool EmbeddedEngine::initWindow(FrontierWindow* window)
{
    EmbeddedWindow* ew = new EmbeddedWindow(this, window);
    ew->init();
    window->setEngineWindow(ew);

    return true;
}

bool EmbeddedEngine::checkEvents()
{
    return true;
}


std::string EmbeddedEngine::getConfigDir()
{
    return string("/tmp");
}


void EmbeddedEngine::message(std::string title, std::string message)
{
}

bool EmbeddedEngine::confirmBox(std::string title, std::string message)
{
    return true;
}

std::string EmbeddedEngine::chooseFile(int flags, std::string path, std::string pattern)
{
    return string("/tmp/test.txt");
}

