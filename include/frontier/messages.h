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

#ifndef __FRONTIER_EVENTS_H_
#define __FRONTIER_EVENTS_H_

#include <frontier/keycodes.h>

#include <string>

namespace Frontier {

class FrontierWindow;

enum MessageType
{
    FRONTIER_MSG_INPUT = 1,
};

struct Message
{
    uint32_t messageType;
};

/*
 * User Input Events
 */

enum InputMessageType
{
    FRONTIER_MSG_INPUT_KEY = 1,
    FRONTIER_MSG_INPUT_MOUSE_BUTTON = 2,
    FRONTIER_MSG_INPUT_MOUSE_MOTION = 3,
    FRONTIER_MSG_INPUT_MOUSE_WHEEL  = 4
};

enum MouseButton
{
    BUTTON_LEFT  = 1,
    BUTTON_RIGHT = 2
};

struct InputMessage : public Message
{
    InputMessageType inputMessageType;
    FrontierWindow* window;

    union
    {
        struct
        {
            bool direction;
            uint32_t key;
            wchar_t chr;
            uint32_t modifiers;
        } key;
        struct
        {
            uint32_t x;
            uint32_t y;
        } motion;
        struct
        {
            uint32_t x;
            uint32_t y;

            bool direction;
            int buttons;
            bool doubleClick;
        } button;
        struct
        {
            uint32_t x;
            uint32_t y;
            int32_t scrollX;
            int32_t scrollY;
        } wheel;
    } event;
};

};

#endif

