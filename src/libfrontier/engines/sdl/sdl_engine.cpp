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


#include "sdl_engine.h"

using namespace std;
using namespace Geek;
using namespace Frontier;

#define SDLK_SCANCODE_MASK (1<<30)

FrontierEngineSDL::FrontierEngineSDL(FrontierApp* app) : FrontierEngine(app)
{
    m_lastText = "";
    m_keyDownMessage = NULL;
}

FrontierEngineSDL::~FrontierEngineSDL()
{
}


bool FrontierEngineSDL::init()
{
    int res;
    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (res < 0)
    {
        log(ERROR, "Failed to initialise SDL!");
    }

    return true;
}

bool FrontierEngineSDL::initWindow(FrontierWindow* window)
{
    bool res;

    FrontierEngineWindowSDL* few = new FrontierEngineWindowSDL(window);

    res = few->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(few);

    return true;
}

static FrontierEngineWindowSDL* getWindow(uint32_t id)
{
    SDL_Window* window = SDL_GetWindowFromID(id);
    if (window == NULL)
    {
        return NULL;
    }

    return (FrontierEngineWindowSDL*)SDL_GetWindowData(window, "FrontierWindow");
}

bool FrontierEngineSDL::checkEvents()
{
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
        {
            return false;
        } break;

        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
        {
            FrontierEngineWindowSDL* few = getWindow(event.button.windowID);
            if (few == NULL)
            {
                return true;
            }

            InputMessage* msg = new InputMessage();
            msg->messageType = FRONTIER_MSG_INPUT;
            msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_BUTTON;
            msg->event.button.direction =
                (event.button.type == SDL_MOUSEBUTTONDOWN);

            msg->event.button.buttons = 0;
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                msg->event.button.buttons = BUTTON_LEFT;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                msg->event.button.buttons = BUTTON_RIGHT;
            }

            msg->event.button.doubleClick = (event.button.clicks == 2);

            msg->event.button.x = event.button.x;
            msg->event.button.y = event.button.y;
            printf("FrontierEngineSDL::checkEvents: few=%p, x=%d, y=%d\n", few, msg->event.button.x, msg->event.button.y);
            few->getWindow()->handleMessage(msg);
        } break;

        case SDL_MOUSEMOTION:
        {
            FrontierEngineWindowSDL* few = getWindow(event.button.windowID);
            if (few == NULL)
            {
                return true;
            }

            InputMessage* msg = new InputMessage();
            msg->messageType = FRONTIER_MSG_INPUT;
            msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_MOTION;
            msg->event.button.x = event.button.x;
            msg->event.button.y = event.button.y;

            few->getWindow()->handleMessage(msg);
        } break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {

            InputMessage* msg = new InputMessage();
            msg->messageType = FRONTIER_MSG_INPUT;
            msg->inputMessageType = FRONTIER_MSG_INPUT_KEY;
            msg->event.key.direction = (event.type == SDL_KEYDOWN);
            msg->event.key.key = event.key.keysym.sym;

            const char* scancodename = SDLCALL SDL_GetScancodeName(event.key.keysym.scancode);
            const char* keyname = SDLCALL SDL_GetKeyName(event.key.keysym.sym);

            if (event.type == SDL_KEYUP)
            {
                printf("FrontierEngineSDL::checkEvents: SDL_KEYUP: scancode=0x%x (%s), sym=0x%x (%s): lastText=%s\n", event.key.keysym.scancode, scancodename, event.key.keysym.sym, keyname, m_lastText.c_str());
                if (m_lastText.length() > 0)
                {
                    msg->event.key.chr = m_lastText.at(0);
                }
                m_lastText = "";

                FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                few->getWindow()->handleMessage(msg);
            }
            else
            {
                if (isprint(event.key.keysym.sym) && !(event.key.keysym.sym & SDLK_SCANCODE_MASK))
                {
                    m_keyDownMessage = msg;
                }
                else
                {
                    m_keyDownMessage = NULL;
                    FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                    few->getWindow()->handleMessage(msg);
                }
            }

        } break;

        case SDL_TEXTINPUT:
        {
            if (m_keyDownMessage != NULL)
            {
                printf("FrontierEngineSDL::checkEvents: SDL_TEXTINPUT: Sending DOWN: chr=%s, key=0x%x, mod=0x%x\n", event.text.text, m_keyDownMessage->event.key.key, m_keyDownMessage->event.key.modifiers);
                m_lastText = string(event.text.text);

                InputMessage* msgCopy = new InputMessage();
                *msgCopy = *m_keyDownMessage;
                if (m_lastText.length() > 0)
                {
                    msgCopy->event.key.chr = m_lastText.at(0);
                }

                FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                few->getWindow()->handleMessage(msgCopy);
            }
            else
            {
                printf("FrontierEngineSDL::checkEvents: SDL_TEXTINPUT: m_keyDownMessage is NULL\n");
            }
        } break;

        case SDL_TEXTEDITING:
            printf("FrontierEngineSDL::checkEvents: SDL_TEXTEDITING: Here: %s\n", event.text.text);
            break;

        case SDL_WINDOWEVENT:
        {
            FrontierEngineWindowSDL* few = getWindow(event.window.windowID);

            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    few->getWindow()->setSize(Size(event.window.data1, event.window.data2));
                    few->getWindow()->update();
                    printf("FrontierEngineSDL::checkEvents: SDL_WINDOWEVENT_RESIZED\n");
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    printf("FrontierEngineSDL::checkEvents: SDL_WINDOWEVENT_SIZE_CHANGED\n");
                    break;
            }
        } break;
    }

    return true;
}

