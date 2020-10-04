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

#ifndef __FRONTIER_EMBEDDED_H_
#define __FRONTIER_EMBEDDED_H_

#include <frontier/engine.h>

namespace Frontier
{

class EmbeddedWindow : public Frontier::FrontierEngineWindow
{
 private:
    Geek::Vector2D m_position;

 public:
    EmbeddedWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    ~EmbeddedWindow() override;

    bool init() override;
    void show() override;
    void hide() override;
    bool update() override;

    void setPosition(unsigned int x, unsigned int y) override { m_position.x = x; m_position.y = y; }
    Geek::Vector2D getPosition() override { return m_position; }

    float getScaleFactor() override;
};

/**
 * \brief An Engine designed for embedding Frontier UIs in to other applications
 *
 * \ingroup engines
 */
class EmbeddedEngine : public FrontierEngine
{
 protected:
    float m_scaleFactor;
    Frontier::Size m_screenSize;

 public:
    explicit EmbeddedEngine(FrontierApp* app);
    ~EmbeddedEngine() override;

    bool init() override;

    bool initWindow(FrontierWindow* window) override;

    bool checkEvents() override;

    std::string getConfigDir() override;

    // Dialogs
    void message(std::string title, std::string message) override;
    bool confirmBox(std::string title, std::string message) override;
    std::string chooseFile(int flags, std::string path, std::string pattern) override;

    void setScreenSize(Frontier::Size size) { m_screenSize = size; }
    Frontier::Size getScreenSize() { return m_screenSize; }

    void setScaleFactor(float factor) { m_scaleFactor = factor; }
    float getScaleFactor() const { return m_scaleFactor; }
};

}

#endif
