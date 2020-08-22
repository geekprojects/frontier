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

#ifndef __CONTROL_PANEL_VIDEO_WIDGET_H_
#define __CONTROL_PANEL_VIDEO_WIDGET_H_

#include <frontier/widgets.h>
#include <frontier/engines/opengl.h>
#include <mpv/client.h>
#include <mpv/render_gl.h>

class VideoWidget : public Frontier::OpenGLDirectWidget
{
 private:
    bool m_addedDirect;
    mpv_handle* m_mpv;
    mpv_render_context* m_mpvGL;
    unsigned int m_fbo;

    std::string m_file;

    Frontier::Size m_textureSize;
    unsigned int m_texture;

 protected:
    virtual void init();
    void onShow();

 public:
    VideoWidget(Frontier::FrontierApp* app);
    virtual ~VideoWidget();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual void directBeforeDraw();
    virtual void directDraw();

    virtual Widget* handleEvent(Frontier::Event* event);

    void setFile(std::string file);
    void play();
    void stop();

    void mpvEvent();
    void mpvRender();

};

#endif
