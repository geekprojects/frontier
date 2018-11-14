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


#include <frontier/engine.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

FrontierEngine::FrontierEngine(FrontierApp* app) : Geek::Logger("FrontierEngine")
{
    m_app = app;
}

FrontierEngine::~FrontierEngine()
{
}

bool FrontierEngine::init()
{
    return true;
}

bool FrontierEngine::initWindow(FrontierWindow* window)
{
    return true;
}

bool FrontierEngine::checkEvents()
{
    // Just quit
    return false;
}

string FrontierEngine::getConfigDir()
{
    wstring name = m_app->getName();

    string dirname = "";
    size_t i;
    for (i = 0; i < name.length(); i++)
    {
        char c = name.at(i);
        if (isalnum(c))
        {
            dirname += tolower(c);
        }
    }

    string home = string(getenv("HOME"));
    return home + "/." + dirname;
}

void FrontierEngine::message(string title, string message)
{
}

bool FrontierEngine::confirmBox(string title, string message)
{
    return false;
}

string FrontierEngine::chooseFile()
{
    log(WARN, "chooseFile not implemented");
    return "";
}

FrontierEngineWindow::FrontierEngineWindow(FrontierWindow* window)
{
     m_window = window;
}

FrontierEngineWindow::~FrontierEngineWindow()
{
}

bool FrontierEngineWindow::init()
{
    return true;
}

void FrontierEngineWindow::show()
{
}

void FrontierEngineWindow::hide()
{
}

bool FrontierEngineWindow::update()
{
    return true;
}

void FrontierEngineWindow::setPosition(unsigned int x, unsigned int y)
{
}

Geek::Vector2D FrontierEngineWindow::getPosition()
{
    return Geek::Vector2D(0, 0);
}

float FrontierEngineWindow::getScaleFactor()
{
    return 1.0;
}

void FrontierEngineWindow::resetCursor()
{
}

void FrontierEngineWindow::updateCursor(WindowCursor cursor, int x, int y, int w, int h)
{
}

