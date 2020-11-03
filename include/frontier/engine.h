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

#ifndef __FRONTIER_ENGINE_H_
#define __FRONTIER_ENGINE_H_

#include <frontier/frontier.h>

#include <geek/core-logger.h>

#include <string>

namespace Frontier {

/**
 * \defgroup engines Engines
 */

/**
 * \brief An Engine provides the interface with the OS
 *
 * \ingroup engines
 */
class FrontierEngine : public Geek::Logger
{
 protected:
    FrontierApp* m_app;

 public:
    explicit FrontierEngine(FrontierApp* app);
    virtual ~FrontierEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual bool quit(bool force);

    virtual std::string getConfigDir();

    // Dialogs
    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);
    virtual ColourPickerWindow* openColourPickerWindow(Geek::Gfx::Colour colour);

    // Features
    /// Returns whether the OS provides it's own native Menus (e.g. MacOS)
    virtual bool providesMenus();
};

class FrontierEngineWindow : public Geek::Logger
{
 protected:
    FrontierEngine* m_engine;
    FrontierWindow* m_window;

 public:
    FrontierEngineWindow(FrontierEngine* engine, FrontierWindow* window);
    virtual ~FrontierEngineWindow();

    virtual bool init();
    virtual void show();
    virtual void hide();

    virtual bool update();

    FrontierEngine* getEngine() { return m_engine; }
    FrontierWindow* getWindow() { return m_window; }

    virtual void setPosition(unsigned int x, unsigned int y);
    virtual Geek::Vector2D getPosition();

    virtual float getScaleFactor();

    virtual void resetCursor();
    virtual void updateCursor(Frontier::WindowCursor cursor, int x, int y, int w, int h);

    virtual void requestUpdate();
};

class EngineInit
{
 private:
 public:
    EngineInit() = default;
    virtual ~EngineInit() = default;

    virtual FrontierEngine* create(FrontierApp* app) { return NULL; }

    virtual const std::string getName() { return ""; }
};

class EngineRegistry : public Geek::Logger
{
 private:
    std::map<std::string, EngineInit*> m_engines;

 public:
    EngineRegistry();
    virtual ~EngineRegistry();

    static void registerEngine(EngineInit* init);
    static FrontierEngine* createEngine(FrontierApp* app, std::string name);
};

#define FRONTIER_ENGINE(_name, _class) \
    namespace Frontier::Engine { \
    class _name##EngineInit : public Frontier::EngineInit \
    { \
     private: \
        static _name##EngineInit* const init __attribute__ ((unused)); \
     public: \
        _name##EngineInit() \
        { \
            EngineRegistry::registerEngine(this); \
        } \
        const std::string getName() \
        { \
            return #_name; \
        } \
        _class* create(FrontierApp* app) \
        { \
            return new _class(app); \
        } \
    }; \
    _name##EngineInit* const _name##EngineInit::init = new _name##EngineInit(); \
    };

}

#endif
