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

#ifndef __FRONTIER_OPENGL_H_
#define __FRONTIER_OPENGL_H_

#ifdef __APPLE__
#include <GLUT/glut.h>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED 1
#include <OpenGL/OpenGLAvailability.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glut.h>
#endif

#include <frontier/frontier.h>
#include <frontier/widgets.h>
#include <frontier/engines/windowing.h>

namespace Frontier
{

class OpenGLEngine;

class OpenGLDirectWidget : public Frontier::Widget
{
 public:
    OpenGLDirectWidget(FrontierApp* ui, std::wstring name);
    OpenGLDirectWidget(FrontierWindow* window, std::wstring name);
    virtual ~OpenGLDirectWidget() {}

    virtual void directBeforeDraw() = 0;
    virtual void directDraw() = 0;

    void setViewport();
};

class OpenGLEngineWindow : public Frontier::WindowingEngineWindow
{
 protected:
    unsigned int m_texture;
    unsigned int m_sampler;
    float m_textureCoordX;
    float m_textureCoordY;
    bool m_textureValid;
    Geek::Gfx::Surface* m_textureSurface;

    std::vector<OpenGLDirectWidget*> m_directWidgets;

 public:
    OpenGLEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~OpenGLEngineWindow();

    virtual bool init();

    virtual bool update();

    void addDirectWidget(OpenGLDirectWidget* widget) { m_directWidgets.push_back(widget); }
    std::vector<OpenGLDirectWidget*> getDirectWidgets() { return m_directWidgets; }
};

/**
 * \brief An Engine designed for embedding Frontier UIs in to OpenGL applications
 *
 * \ingroup engines
 */
class OpenGLApp : public Frontier::FrontierApp
{
 protected:

 public:
    OpenGLApp();
    OpenGLApp(std::wstring appName);
    virtual ~OpenGLApp();

    virtual bool init();

    void setScreenSize(Size size);

    void mouseMotion(int x, int y);
    void mouseButton(int x, int y, int button, bool direction);

    virtual void draw();
};

class OpenGLEngine : public WindowingEngine
{
 protected:

 public:
    OpenGLEngine(FrontierApp* app);
    virtual ~OpenGLEngine();

    virtual bool initWindow(FrontierWindow* window);
};

class OpenGLTexture
{
private:
    unsigned int m_texture;
    unsigned int m_sampler;
    bool m_textureValid;

 protected:
    Geek::Gfx::Surface* m_surface;

    bool generateTexture();

 public:
    OpenGLTexture(Geek::Gfx::Surface* surface);
    virtual ~OpenGLTexture();

    void bind();

    unsigned int getTexture() { return m_texture; }
    unsigned int getSampler() { return m_sampler; }
};

};

#endif
