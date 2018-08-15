#ifndef __FRONTIER_ENGINE_SDL_H_
#define __FRONTIER_ENGINE_SDL_H_

#include <frontier/engine.h>

#include <SDL.h>
#include <SDL_video.h>

class FrontierEngineWindowSDL : public FrontierEngineWindow
{
 private:
    SDL_Window* m_sdlWindow;

 public:
    FrontierEngineWindowSDL(FrontierWindow* window);
    virtual ~FrontierEngineWindowSDL();

    virtual bool init();
    virtual bool show();
    virtual bool update();
};

class FrontierEngineSDL : public FrontierEngine
{
 private:
    

 public:
    FrontierEngineSDL(FrontierApp* app);
    virtual ~FrontierEngineSDL();

    bool init();
    bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();
};

#endif
