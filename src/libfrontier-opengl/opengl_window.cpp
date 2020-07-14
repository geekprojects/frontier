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


#include <frontier/engines/opengl.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

OpenGLEngineWindow::OpenGLEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window)
    : WindowingEngineWindow(engine, window)
{
    m_textureSurface = NULL;
    m_textureValid = false;

    glGenTextures(1, &m_texture);
}

OpenGLEngineWindow::~OpenGLEngineWindow()
{
}

bool OpenGLEngineWindow::init()
{
    return WindowingEngineWindow::init();
}

static int powerOfTwo(int input)
{
    int value = 1;

    while (value < input)
    {
        value <<= 1;
    }
    return value;
}

bool OpenGLEngineWindow::update()
{
    Size size = getWindow()->getSize();
//log(DEBUG, "draw: width=%d, height=%d", size.width, size.height);

    float scale = getScaleFactor();

    unsigned int textureWidth = powerOfTwo(size.width * scale);
    unsigned int textureHeight = powerOfTwo(size.height * scale);
    m_textureCoordX = (float)(size.width * scale) / (float)textureWidth;
    m_textureCoordY = (float)(size.height * scale) / (float)textureHeight;

    if (m_textureSurface == NULL || m_textureSurface->getWidth() != textureWidth || m_textureSurface->getHeight() != textureHeight )
    {
        if (m_textureSurface != NULL)
        {
            delete m_textureSurface;
        }
        m_textureSurface = new Surface(textureWidth, textureHeight, 4);
    }

    Geek::Gfx::Surface* surface = getWindow()->getSurface();
    m_textureSurface->blit(0, 0, surface);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        m_textureSurface->getWidth(), m_textureSurface->getHeight(),
        0,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        m_textureSurface->getData());

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_TRIANGLE_STRIP);

    Vector2D position = getPosition();

    glTexCoord2f(0, 0);
    glVertex2i(position.x, position.y);

    glTexCoord2f(m_textureCoordX, 0);
    glVertex2i(position.x + (size.width * scale), position.y);

    glTexCoord2f(0, m_textureCoordY);
    glVertex2i(position.x, position.y + (size.height * scale));

    glTexCoord2f(m_textureCoordX, m_textureCoordY);
    glVertex2i(position.x + (size.width * scale), position.y + (size.height * scale));

    glEnd();

    for (OpenGLDirectWidget* widget: m_directWidgets)
    {
        Widget* fwidget = dynamic_cast<Widget*>(widget);
        if (fwidget->isVisible())
        {
            widget->directDraw();
        }
    }
    glBindTexture(GL_TEXTURE_2D, m_texture);

    return true;
}

