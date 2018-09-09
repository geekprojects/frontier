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

enum MessageType
{
    FRONTIER_MSG_INPUT = 1,
    FRONTIER_MSG_UI = 2,
    FRONTIER_MSG_APP = 1000
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
    FRONTIER_MSG_INPUT_MOUSE_MOTION = 3
};

struct InputMessage : public Message
{
    InputMessageType inputMessageType;

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
            uint8_t button;
            bool doubleClick;
        } button;
    } event;
};


/*
 * UI/Widget generated events
 */
class Widget;

struct UIMessage : public Frontier::Message
{
    int uiMessageType;
    Widget* widget;
    Frontier::Message* source;
    struct
    {
        bool state;
    } button;
    struct
    {
        int selected;
        int itemY;
    } list;
};

#define FRONTIER_MSG_UI_BUTTON_PRESSED 0x1000
#define FRONTIER_MSG_UI_LIST_SELECTED 0x2000


/*
 * Application Specific Messages
 */

#define FRONTIER_MSG_APP_QUIT 1

struct AppMessage : public Message
{
    uint32_t appMessageType;
};


};

#endif

