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

#ifndef __FRONTIER_ENGINE_H_
#define __FRONTIER_ENGINE_H_

#include <frontier/frontier.h>

#include <geek/core-logger.h>

namespace Frontier {

class FrontierEngine : public Geek::Logger
{
 private:
    FrontierApp* m_app;

 public:
    FrontierEngine(FrontierApp* app);
    virtual ~FrontierEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual std::string chooseFile();
};

class FrontierEngineWindow
{
 protected:
    FrontierWindow* m_window;

 public:
    FrontierEngineWindow(FrontierWindow* window);
    virtual ~FrontierEngineWindow();

    virtual bool init();
    virtual bool show();

    virtual bool update();

    FrontierWindow* getWindow() { return m_window; }

    virtual float getScaleFactor();
};

};

#endif
