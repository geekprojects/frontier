
#include "sdl_engine.h"

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

SDL_SetWindowData(m_sdlWindow, "FrontierWindow", this);

    return true;
}

bool FrontierEngineWindowSDL::show()
{
    return true;
}

bool FrontierEngineWindowSDL::update()
{
    int w = m_window->getWidth();
    int h = m_window->getHeight();

    SDL_SetWindowSize(m_sdlWindow, w, h);

    SDL_Surface* sdlSurface = SDL_GetWindowSurface(m_sdlWindow);

m_window->getSurface()->drawRectFilled(0, 0, 20, 20, 0xff);

    int res;
    res = SDL_ConvertPixels(
        w, h,
        SDL_PIXELFORMAT_ABGR8888, m_window->getSurface()->getData(), w * 4,
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

