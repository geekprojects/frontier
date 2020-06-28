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


#include <frontier/engines/windowing.h>

using namespace Frontier;
using namespace std;

WindowingEngine::WindowingEngine(FrontierApp* app) : EmbeddedEngine(app)
{
}

WindowingEngine::~WindowingEngine()
{
}


void WindowingEngine::showWindow(FrontierWindow* window)
{
    hideWindow(window);

    m_windowOrder.push_front(window);

}

void WindowingEngine::hideWindow(FrontierWindow* window)
{
    for (auto it = m_windowOrder.begin(); it != m_windowOrder.end(); it++)
    {
        if (*it == window)
        {
            m_windowOrder.erase(it);
            break;
        }
    }
}

FrontierWindow* WindowingEngine::windowAt(int x, int y)
{
    for (auto w : m_windowOrder)
    {
        if (w->getRect().intersects(x, y))
        {
            return w;
        }
    }
    return NULL;
}


void WindowingEngine::mouseMotion(int x, int y)
{
    FrontierWindow* window = windowAt(x, y);
    if (window != NULL)
    {
        MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
        mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
        mouseMotionEvent->x = x - window->getPosition().x;
        mouseMotionEvent->y = y - window->getPosition().y;
        window->handleEvent(mouseMotionEvent);
    }
}

void WindowingEngine::mouseButton(int x, int y, int button, bool direction)
{
    FrontierWindow* window = windowAt(x, y);
    if (window != NULL)
    {
        // Bring it to the front
        showWindow(window);

        MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
        mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
        mouseButtonEvent->direction = direction;
        mouseButtonEvent->buttons = button;
        mouseButtonEvent->x = x - window->getPosition().x;
        mouseButtonEvent->y = y - window->getPosition().y;
        window->handleEvent(mouseButtonEvent);
    }
}


