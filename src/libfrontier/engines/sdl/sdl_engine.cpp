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
    m_keyDownEvent = NULL;
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

    m_redrawWindowEvent = SDL_RegisterEvents(1);

    return true;
}

bool FrontierEngineSDL::initWindow(FrontierWindow* window)
{
    bool res;

    FrontierEngineWindowSDL* few = new FrontierEngineWindowSDL(this, window);

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
#if SDL_VERSION_ATLEAST(2, 0, 12)
            if (event.button.button == (uint8_t)SDL_TOUCH_MOUSEID)
            {
                // Handled by SDL_FINGERx below
                return true;
            }
#endif

            FrontierEngineWindowSDL* few = getWindow(event.button.windowID);
            if (few == NULL)
            {
                return true;
            }

            MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
            mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
            mouseButtonEvent->direction = (event.button.type == SDL_MOUSEBUTTONDOWN);

            mouseButtonEvent->buttons = 0;
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseButtonEvent->buttons = BUTTON_LEFT;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouseButtonEvent->buttons = BUTTON_RIGHT;
            }

            mouseButtonEvent->doubleClick = (event.button.clicks == 2);

            mouseButtonEvent->x = event.button.x;
            mouseButtonEvent->y = event.button.y;
            log(DEBUG, "checkEvents: few=%p, x=%d, y=%d", few, mouseButtonEvent->x, mouseButtonEvent->y);
            few->getWindow()->handleEvent(mouseButtonEvent);
        } break;

#if SDL_VERSION_ATLEAST(2, 0, 12)
        case SDL_FINGERUP:
        case SDL_FINGERDOWN:
        {
            FrontierEngineWindowSDL* few = getWindow(event.tfinger.windowID);
            if (few == NULL)
            {
                return true;
            }

            MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
            mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
            mouseButtonEvent->direction = (event.tfinger.type == SDL_FINGERDOWN);

            mouseButtonEvent->buttons = BUTTON_LEFT;

            mouseButtonEvent->x = (uint32_t)(event.tfinger.x * (float)few->getWindow()->getSize().width);
            mouseButtonEvent->y = (uint32_t)(event.tfinger.y * (float)few->getWindow()->getSize().height);
            log(DEBUG, "checkEvents: SDL_FINGERx: few=%p, %0.2f, %0.2f -> x=%d, y=%d", few, event.tfinger.x, event.tfinger.y, mouseButtonEvent->x, mouseButtonEvent->y);
            few->getWindow()->handleEvent(mouseButtonEvent);
        } break;
#endif

        case SDL_MOUSEMOTION:
        {
            FrontierEngineWindowSDL* few = getWindow(event.button.windowID);
            if (few == NULL)
            {
                return true;
            }

            MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
            mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
            mouseMotionEvent->x = event.button.x;
            mouseMotionEvent->y = event.button.y;

            few->getWindow()->handleEvent(mouseMotionEvent);
        } break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            KeyEvent* keyEvent = new KeyEvent();
            keyEvent->eventType = FRONTIER_EVENT_KEY;
            keyEvent->direction = (event.type == SDL_KEYDOWN);
            keyEvent->key = event.key.keysym.sym;

            const char* scancodename = SDLCALL SDL_GetScancodeName(event.key.keysym.scancode);
            const char* keyname = SDLCALL SDL_GetKeyName(event.key.keysym.sym);

            if (event.type == SDL_KEYUP)
            {
                log(DEBUG,
                    "checkEvents: SDL_KEYUP: scancode=0x%x (%s), sym=0x%x (%s): lastText=%s",
                    event.key.keysym.scancode,
                    scancodename,
                    event.key.keysym.sym,
                    keyname,
                    m_lastText.c_str());
                if (m_lastText.length() > 0)
                {
                    keyEvent->chr = m_lastText.at(0);
                }
                m_lastText = "";

                FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                few->getWindow()->handleEvent(keyEvent);
            }
            else
            {
                if (isprint(event.key.keysym.sym) && !(event.key.keysym.sym & SDLK_SCANCODE_MASK))
                {
                    m_keyDownEvent = keyEvent;
                }
                else
                {
                    m_keyDownEvent = NULL;
                    FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                    few->getWindow()->handleEvent(keyEvent);
                }
            }

        } break;

        case SDL_TEXTINPUT:
        {
            if (m_keyDownEvent != NULL)
            {
                log(DEBUG,
                    "checkEvents: SDL_TEXTINPUT: Sending DOWN: chr=%s, key=0x%x, mod=0x%x",
                    event.text.text,
                    m_keyDownEvent->key,
                    m_keyDownEvent->modifiers);
                m_lastText = string(event.text.text);

                KeyEvent* eventCopy = new KeyEvent();
                *eventCopy = *m_keyDownEvent;
                if (m_lastText.length() > 0)
                {
                    eventCopy->chr = m_lastText.at(0);
                }

                FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                few->getWindow()->handleEvent(eventCopy);
            }
            else
            {
                log(DEBUG, "checkEvents: SDL_TEXTINPUT: m_keyDownEvent is NULL");
            }
        } break;

        case SDL_TEXTEDITING:
            log(DEBUG, "checkEvents: SDL_TEXTEDITING: Here: %s", event.text.text);
            break;

        case SDL_WINDOWEVENT:
        {
            FrontierEngineWindowSDL* few = getWindow(event.window.windowID);

            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    few->getWindow()->setSize(Size(event.window.data1, event.window.data2));
                    few->getWindow()->update();
                    log(DEBUG, "checkEvents: SDL_WINDOWEVENT_RESIZED");
                    break;

                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    log(DEBUG, "checkEvents: SDL_WINDOWEVENT_SIZE_CHANGED");
                    break;

                case SDL_WINDOWEVENT_SHOWN:
                case SDL_WINDOWEVENT_EXPOSED:
                    log(DEBUG, "checkEvents: SDL_WINDOWEVENT: Forcing update");
                    few->getWindow()->update(true);
                    break;

                default:
                    log(ERROR, "checkEvents: SDL_WINDOWEVENT: Unknown event: %d", event.window.event);
                    break;
            }
        } break;


        default:
            if (event.type == m_redrawWindowEvent)
            {
                FrontierEngineWindowSDL* few = (FrontierEngineWindowSDL*)(event.user.data1);
                few->getWindow()->update(true);
            }
            else
            {
                log(ERROR, "checkEvents: Unhandled event: %d", event.type);
            }
            break;
    }

    return true;
}

void FrontierEngineSDL::requestUpdate(FrontierEngineWindowSDL* window)
{
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    event.type = m_redrawWindowEvent;
    event.user.code = 0;
    event.user.data1 = window;
    event.user.data2 = 0;

    SDL_PushEvent(&event);
}

