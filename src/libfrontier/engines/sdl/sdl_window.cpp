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

using namespace Frontier;
using namespace Geek;

FrontierEngineWindowSDL::FrontierEngineWindowSDL(FrontierWindow* win) : FrontierEngineWindow(win)
{
}

FrontierEngineWindowSDL::~FrontierEngineWindowSDL()
{
}

bool FrontierEngineWindowSDL::init()
{
    int flags =
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_ALLOW_HIGHDPI ;

    m_sdlWindow = SDL_CreateWindow(
        "Frontier",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        flags);

    printf("FrontierEngineWindowSDL::init: m_sdlWindow=%p\n", m_sdlWindow);
    if (m_sdlWindow == NULL)
    {
        return false;
    }

    SDL_SetWindowData(m_sdlWindow, "FrontierWindow", this);

    return true;
}

void FrontierEngineWindowSDL::show()
{
    SDL_ShowWindow(m_sdlWindow);
}

void FrontierEngineWindowSDL::hide()
{
    SDL_HideWindow(m_sdlWindow);
}

bool FrontierEngineWindowSDL::update()
{
    if (m_window->getSurface() == NULL || m_window->getSurface()->getData() == NULL)
    {
        return true;
    }

    Size winSize = m_window->getSize();

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(m_sdlWindow, &w, &h);

    if (w != winSize.width || h != winSize.height)
    {
        SDL_SetWindowSize(m_sdlWindow, winSize.width, winSize.height);
        printf("FrontierEngineWindowSDL::update: Setting window size: %s\n", winSize.toString().c_str());
    }

    SDL_Surface* sdlSurface = SDL_GetWindowSurface(m_sdlWindow);
    if (sdlSurface == NULL)
    {
        return false;
    }

    m_window->getSurface()->drawRectFilled(0, 0, 20, 20, 0xff);

    int res;
    res = SDL_ConvertPixels(
        winSize.width, winSize.height,
        SDL_PIXELFORMAT_ARGB8888, m_window->getSurface()->getData(), winSize.width * 4,
        sdlSurface->format->format, sdlSurface->pixels, sdlSurface->pitch);
    if (res < 0)
    {
        printf("ScreenSDL::redraw: res=%d: %s\n", res, SDL_GetError());
    }

/*
    SDL_Rect dstrect;
    dstrect.x = 100;
    dstrect.y = 100;
    dstrect.w = m_surface->w;
    dstrect.h = m_surface->h;

    SDL_BlitSurface(m_surface, NULL, winSurface, &dstrect);
*/

    SDL_UpdateWindowSurface(m_sdlWindow);

    return true;
}

