/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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

#ifndef __FRONTIER_ENGINES_WINDOWING__H_
#define __FRONTIER_ENGINES_WINDOWING__H_

#include <frontier/engines/embedded.h>
#include <deque>

namespace Frontier
{

class WindowingEngine : public EmbeddedEngine
{
 private:
    std::deque<FrontierWindow*> m_windowOrder;

 public:
    explicit WindowingEngine(FrontierApp* app);
    ~WindowingEngine() override;

    void showWindow(FrontierWindow* window);
    void hideWindow(FrontierWindow* window);
    FrontierWindow* windowAt(int x, int y);

    void mouseMotion(int x, int y);
    void mouseButton(int x, int y, int button, bool direction);

    const std::deque<FrontierWindow*>& getWindowOrder() { return m_windowOrder; }
};

class WindowingEngineWindow : public EmbeddedWindow
{
 private:

 public:
    WindowingEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    ~WindowingEngineWindow() override;

    bool init() override;

    void show() override;
    void hide() override;
};


}

#endif
