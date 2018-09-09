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

using namespace Geek;
using namespace Frontier;

FrontierEngineSDL::FrontierEngineSDL(FrontierApp* app) : FrontierEngine(app)
{
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
            msg->event.button.button = event.button.button;
            msg->event.button.doubleClick = (event.button.clicks == 2);


/*
            if (m_highDPI)
            {
                int screenw;
                int screenh;
                SDL_GetWindowSize(m_screen, &screenw, &screenh);
                int draww;
                    int drawh;
                    SDL_GL_GetDrawableSize(m_screen, &draww, &drawh);
                    msg->event.button.x = (int)((((float)event.button.x / (float)screenw)) * (float)draww);
                    msg->event.button.y = (int)((((float)event.button.y / (float)screenh)) * (float)drawh);
            }
            else
*/
            {
                msg->event.button.x = event.button.x;
                msg->event.button.y = event.button.y;
            }
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

            // Limit motion events to one per frame
/*
            uint64_t t = SDL_GetTicks();
            if ((t - m_lastMotion) < (1000 / 60))
            {
                continue;
            }
            m_lastMotion = t;
*/

            InputMessage* msg = new InputMessage();
            msg->messageType = FRONTIER_MSG_INPUT;
            msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_MOTION;
/*
            if (m_highDPI)
            {
                int screenw;
                int screenh;
                SDL_GetWindowSize(m_screen, &screenw, &screenh);
                int draww;
                int drawh;
                SDL_GL_GetDrawableSize(m_screen, &draww, &drawh);
                msg->event.motion.x = (int)((((float)event.motion.x / (float)screenw)) * (float)draww);
                msg->event.motion.y = (int)((((float)event.motion.y / (float)screenh)) * (float)drawh);
            }
            else
*/
            {
                msg->event.button.x = event.button.x;
                msg->event.button.y = event.button.y;
            }
            few->getWindow()->handleMessage(msg);
        } break;

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

