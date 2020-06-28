/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
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

#ifndef __FRONTIER_EVENTS_H_
#define __FRONTIER_EVENTS_H_

#include <frontier/keycodes.h>

#include <string>

namespace Frontier {

class FrontierWindow;

/*
 * User Input Events
 */

enum EventCategory
{
    FRONTIER_EVENT_KEYBOARD = 0x10000,
    FRONTIER_EVENT_MOUSE    = 0x20000,
    FRONTIER_EVENT_MASK     = 0xFFFF0000
};

enum EventType
{
    FRONTIER_EVENT_KEY =          FRONTIER_EVENT_KEYBOARD | 0x1,
    FRONTIER_EVENT_MOUSE_BUTTON = FRONTIER_EVENT_MOUSE | 0x1,
    FRONTIER_EVENT_MOUSE_MOTION = FRONTIER_EVENT_MOUSE | 0x2,
    FRONTIER_EVENT_MOUSE_SCROLL = FRONTIER_EVENT_MOUSE | 0x3
};

enum MouseButton
{
    BUTTON_LEFT  = 1,
    BUTTON_RIGHT = 2
};

struct Event
{
    EventType eventType;
    FrontierWindow* window;

    bool is(EventCategory category)
    {
        return !!(((unsigned int)eventType & (unsigned int)FRONTIER_EVENT_MASK) == (unsigned int)category);
    }
};


struct KeyEvent : Event
{
    bool direction;
    uint32_t key;
    wchar_t chr;
    uint32_t modifiers;
};

struct MouseEvent : Event
{
    uint32_t x;
    uint32_t y;
};

struct MouseMotionEvent : MouseEvent
{
};

struct MouseButtonEvent : MouseEvent
{
    bool direction;
    int buttons;
    bool doubleClick;
};

struct MouseScrollEvent : MouseEvent
{
    int32_t scrollX;
    int32_t scrollY;
};

};

#endif

