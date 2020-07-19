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


#include "sdl_engine.h"

using namespace std;
using namespace Geek;
using namespace Frontier;

FrontierEngineSDL::FrontierEngineSDL(FrontierApp* app) : FrontierEngine(app)
{
    m_lastMotion = 0;
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

    int i;
    for (i = 32; i < 128; i++)
    {
        m_keycodeTable.insert(make_pair(i, i));
    }
    m_keycodeTable.insert(make_pair(SDLK_BACKSPACE, KC_BACKSPACE));
    m_keycodeTable.insert(make_pair(SDLK_TAB, KC_TAB));
    //m_keycodeTable.insert(make_pair(, KC_LINEFEED));
    m_keycodeTable.insert(make_pair(SDLK_CLEAR, KC_CLEAR));
    m_keycodeTable.insert(make_pair(SDLK_RETURN, KC_RETURN));
    m_keycodeTable.insert(make_pair(SDLK_PAUSE, KC_PAUSE));
    m_keycodeTable.insert(make_pair(SDLK_SCROLLLOCK, KC_SCROLL_LOCK));
    m_keycodeTable.insert(make_pair(SDLK_SYSREQ, KC_SYS_REQ));
    m_keycodeTable.insert(make_pair(SDLK_ESCAPE, KC_ESCAPE));
    m_keycodeTable.insert(make_pair(SDLK_DELETE, KC_DELETE));
    m_keycodeTable.insert(make_pair(SDLK_HOME, KC_HOME));
    m_keycodeTable.insert(make_pair(SDLK_LEFT, KC_LEFT));
    m_keycodeTable.insert(make_pair(SDLK_UP, KC_UP));
    m_keycodeTable.insert(make_pair(SDLK_RIGHT, KC_RIGHT));
    m_keycodeTable.insert(make_pair(SDLK_DOWN, KC_DOWN));
    m_keycodeTable.insert(make_pair(SDLK_PRIOR, KC_PRIOR));
    m_keycodeTable.insert(make_pair(SDLK_PAGEUP, KC_PAGE_UP));
    //m_keycodeTable.insert(make_pair(, KC_NEXT));
    m_keycodeTable.insert(make_pair(SDLK_PAGEDOWN, KC_PAGE_DOWN));
    m_keycodeTable.insert(make_pair(SDLK_END, KC_END));
    //m_keycodeTable.insert(make_pair(, KC_BEGIN));
    m_keycodeTable.insert(make_pair(SDLK_SELECT, KC_SELECT));
    m_keycodeTable.insert(make_pair(SDLK_PRINTSCREEN, KC_PRINT_SCREEN));
    m_keycodeTable.insert(make_pair(SDLK_EXECUTE, KC_EXECUTE));
    m_keycodeTable.insert(make_pair(SDLK_INSERT, KC_INSERT));
    m_keycodeTable.insert(make_pair(SDLK_UNDO, KC_UNDO));
    //m_keycodeTable.insert(make_pair(, KC_REDO));
    //m_keycodeTable.insert(make_pair(, KC_MENU));
    m_keycodeTable.insert(make_pair(SDLK_FIND, KC_FIND));
    m_keycodeTable.insert(make_pair(SDLK_CANCEL, KC_CANCEL));
    m_keycodeTable.insert(make_pair(SDLK_HELP, KC_HELP));
    //m_keycodeTable.insert(make_pair(, KC_BREAK));
    m_keycodeTable.insert(make_pair(SDLK_MODE, KC_MODE_SWITCH));
    //m_keycodeTable.insert(make_pair(, KC_SCRIPT_SWITCH));
    //m_keycodeTable.insert(make_pair(, KC_NUM_LOCK));

    m_keycodeTable.insert(make_pair(SDLK_KP_SPACE, KC_KP_SPACE));
    m_keycodeTable.insert(make_pair(SDLK_KP_TAB, KC_KP_TAB));
    m_keycodeTable.insert(make_pair(SDLK_KP_ENTER, KC_KP_ENTER));
    //m_keycodeTable.insert(make_pair(, KC_KP_F1));
    //m_keycodeTable.insert(make_pair(, KC_KP_F2));
    //m_keycodeTable.insert(make_pair(, KC_KP_F3));
    //m_keycodeTable.insert(make_pair(, KC_KP_F4));
    //m_keycodeTable.insert(make_pair(, KC_KP_HOME;
    //m_keycodeTable.insert(make_pair(, KC_KP_LEFT));
    //m_keycodeTable.insert(make_pair(, KC_KP_UP));
    //m_keycodeTable.insert(make_pair(, KC_KP_RIGHT));
    //m_keycodeTable.insert(make_pair(, KC_KP_DOWN));
    //m_keycodeTable.insert(make_pair(, KC_KP_PRIOR));
    //m_keycodeTable.insert(make_pair(, KC_KP_PAGE_UP));
    //m_keycodeTable.insert(make_pair(, KC_KP_NEXT));
    //m_keycodeTable.insert(make_pair(, KC_KP_PAGE_DOWN));
    //m_keycodeTable.insert(make_pair(, KC_KP_END));
    //m_keycodeTable.insert(make_pair(, KC_KP_BEGIN));
    //m_keycodeTable.insert(make_pair(, KC_KP_INSERT));
    //m_keycodeTable.insert(make_pair(, KC_KP_DELETE));
    m_keycodeTable.insert(make_pair(SDLK_KP_EQUALS, KC_KP_EQUAL));
    m_keycodeTable.insert(make_pair(SDLK_KP_MULTIPLY, KC_KP_MULTIPLY));
    m_keycodeTable.insert(make_pair(SDLK_KP_PLUS, KC_KP_ADD));
    m_keycodeTable.insert(make_pair(SDLK_KP_COMMA, KC_KP_COMMA));
    m_keycodeTable.insert(make_pair(SDLK_KP_MINUS, KC_KP_SUBTRACT));
    m_keycodeTable.insert(make_pair(SDLK_KP_DECIMAL, KC_KP_DECIMAL));
    m_keycodeTable.insert(make_pair(SDLK_KP_DIVIDE, KC_KP_DIVIDE));
    m_keycodeTable.insert(make_pair(SDLK_KP_0, KC_KP_0));
    m_keycodeTable.insert(make_pair(SDLK_KP_1, KC_KP_1));
    m_keycodeTable.insert(make_pair(SDLK_KP_2, KC_KP_2));
    m_keycodeTable.insert(make_pair(SDLK_KP_3, KC_KP_3));
    m_keycodeTable.insert(make_pair(SDLK_KP_4, KC_KP_4));
    m_keycodeTable.insert(make_pair(SDLK_KP_5, KC_KP_5));
    m_keycodeTable.insert(make_pair(SDLK_KP_6, KC_KP_6));
    m_keycodeTable.insert(make_pair(SDLK_KP_7, KC_KP_7));
    m_keycodeTable.insert(make_pair(SDLK_KP_8, KC_KP_8));
    m_keycodeTable.insert(make_pair(SDLK_KP_8, KC_KP_9));

    m_keycodeTable.insert(make_pair(SDLK_F1, KC_F1));
    m_keycodeTable.insert(make_pair(SDLK_F2, KC_F2));
    m_keycodeTable.insert(make_pair(SDLK_F3, KC_F3));
    m_keycodeTable.insert(make_pair(SDLK_F4, KC_F4));
    m_keycodeTable.insert(make_pair(SDLK_F5, KC_F5));
    m_keycodeTable.insert(make_pair(SDLK_F6, KC_F6));
    m_keycodeTable.insert(make_pair(SDLK_F7, KC_F7));
    m_keycodeTable.insert(make_pair(SDLK_F8, KC_F8));
    m_keycodeTable.insert(make_pair(SDLK_F9, KC_F9));
    m_keycodeTable.insert(make_pair(SDLK_F10, KC_F10));
    m_keycodeTable.insert(make_pair(SDLK_F11, KC_F11));
    m_keycodeTable.insert(make_pair(SDLK_F12, KC_F12));

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
            m_lastMouseX = event.button.x;
            m_lastMouseY = event.button.y;
        } break;

        case SDL_MOUSEWHEEL:
        {
            FrontierEngineWindowSDL* few = getWindow(event.wheel.windowID);
            if (few == NULL)
            {
                return true;
            }

            Frontier::MouseScrollEvent* mouseScrollEvent = new Frontier::MouseScrollEvent();
            mouseScrollEvent->eventType = FRONTIER_EVENT_MOUSE_SCROLL;

            mouseScrollEvent->x = m_lastMouseX;
            mouseScrollEvent->y = m_lastMouseY;
            mouseScrollEvent->scrollX = event.wheel.x * 2;
            mouseScrollEvent->scrollY = event.wheel.y * 2;

            few->getWindow()->handleEvent(mouseScrollEvent);

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

            m_lastMouseX = mouseButtonEvent->x;
            m_lastMouseY = mouseButtonEvent->y;
        } break;
#endif

        case SDL_MOUSEMOTION:
        {
            uint32_t now = SDL_GetTicks();
            if (((now - event.motion.timestamp) > 50) && ((event.motion.timestamp - m_lastMotion) < 100))
            {
                log(DEBUG, "checkEvents: SDL_MOUSEMOTION: Ignoring!");
                // It has been too long, ignore
                return true;
            }

            FrontierEngineWindowSDL* few = getWindow(event.motion.windowID);
            if (few == NULL)
            {
                return true;
            }

            m_lastMotion = event.motion.timestamp;

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

            map<uint32_t, uint32_t>::iterator it = m_keycodeTable.find(event.key.keysym.sym);
            if (it != m_keycodeTable.end())
            {

                keyEvent->key = it->second;
                keyEvent->chr = 0;
                if (!(event.key.keysym.sym & SDLK_SCANCODE_MASK) && iswprint(event.key.keysym.sym))
                {
                    keyEvent->chr = event.key.keysym.sym;
                }

                keyEvent->modifiers = 0;
                if (event.key.keysym.mod & KMOD_LSHIFT)
                {
                    keyEvent->modifiers |= KeyModifier::KMOD_SHIFT_L;
                }
                if (event.key.keysym.mod & KMOD_RSHIFT)
                {
                    keyEvent->modifiers |= KeyModifier::KMOD_SHIFT_R;
                }

                if (keyEvent->modifiers & (KeyModifier::KMOD_SHIFT_L | KeyModifier::KMOD_SHIFT_R))
                {
                    keyEvent->chr = toupper(keyEvent->chr);
                }

                if (event.type == SDL_KEYUP || (keyEvent->chr == 0))
                {
                    FrontierEngineWindowSDL* few = getWindow(event.key.windowID);
                    few->getWindow()->handleEvent(keyEvent);
                    m_lastText = "";
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    m_keyDownEvent = keyEvent;
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
                m_keyDownEvent = NULL;
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
                case SDL_WINDOWEVENT_MOVED:
                case SDL_WINDOWEVENT_ENTER:
                case SDL_WINDOWEVENT_LEAVE:
                case SDL_WINDOWEVENT_TAKE_FOCUS:
                    // Ignore
                    break;

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

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    m_app->setActiveWindow(few->getWindow());
                    break;

                case SDL_WINDOWEVENT_CLOSE:
                    few->getWindow()->closeSignal().emit();
                    break;

                default:
                    log(ERROR, "checkEvents: SDL_WINDOWEVENT: Unknown event: %d", event.window.event);
                    break;
            }
        } break;

        case SDL_AUDIODEVICEADDED:
            // Ignore
            break;

        default:
            if (event.type == m_redrawWindowEvent)
            {
                FrontierEngineWindowSDL* few = (FrontierEngineWindowSDL*)(event.user.data1);
                few->getWindow()->update(true);
            }
            else
            {
                log(ERROR, "checkEvents: Unhandled event: 0x%x (%d)", event.type, event.type);
            }
            break;
    }

    return true;
}

bool FrontierEngineSDL::quit(bool force)
{
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    event.type = SDL_QUIT;

    SDL_PushEvent(&event);

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

