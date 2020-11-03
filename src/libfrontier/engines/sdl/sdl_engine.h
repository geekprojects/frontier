/* * Frontier - A toolkit for creating simple OS-independent user interfaces
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

#ifndef __FRONTIER_ENGINE_SDL_H_
#define __FRONTIER_ENGINE_SDL_H_

#include <frontier/engine.h>

#undef malloc
#undef HAVE_MALLOC

#include <SDL.h>
#include <SDL_video.h>

namespace Frontier
{

class FrontierEngineWindowSDL : public Frontier::FrontierEngineWindow
{
 private:
    SDL_Window* m_sdlWindow;

 public:
    FrontierEngineWindowSDL(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~FrontierEngineWindowSDL();

    virtual bool init();
    virtual void show();
    virtual void hide();
    virtual bool update();

    virtual void setPosition(unsigned int x, unsigned int y);
    virtual Geek::Vector2D getPosition();

    virtual void requestUpdate();
};

class FrontierEngineSDL : public Frontier::FrontierEngine
{
 private:

    std::map<uint32_t, uint32_t> m_keycodeTable;

    int m_lastMotion;
    int m_lastMouseX;
    int m_lastMouseY;
    std::string m_lastText;

    Frontier::KeyEvent* m_keyDownEvent;

    uint32_t m_redrawWindowEvent;

 public:
    FrontierEngineSDL(Frontier::FrontierApp* app);
    virtual ~FrontierEngineSDL();

    bool init();
    bool initWindow(Frontier::FrontierWindow* window);

    bool quit(bool force = false);

    virtual bool checkEvents();

    void requestUpdate(FrontierEngineWindowSDL* window);
};

}

#endif
