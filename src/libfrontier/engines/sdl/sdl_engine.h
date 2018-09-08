#ifndef __FRONTIER_ENGINE_SDL_H_
#define __FRONTIER_ENGINE_SDL_H_

#include <frontier/engine.h>

#undef malloc
#undef HAVE_MALLOC

#include <SDL.h>
#include <SDL_video.h>

class FrontierEngineWindowSDL : public Frontier::FrontierEngineWindow
{
 private:
    SDL_Window* m_sdlWindow;

 public:
    FrontierEngineWindowSDL(Frontier::FrontierWindow* window);
    virtual ~FrontierEngineWindowSDL();

    virtual bool init();
    virtual bool show();
    virtual bool update();
};

class FrontierEngineSDL : public Frontier::FrontierEngine
{
 private:
    

 public:
    FrontierEngineSDL(Frontier::FrontierApp* app);
    virtual ~FrontierEngineSDL();

    bool init();
    bool initWindow(Frontier::FrontierWindow* window);

    virtual bool checkEvents();
};

#endif
