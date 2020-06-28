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



#include <frontier/widgets/video.h>

#include <dlfcn.h>

#ifdef __APPLE__
#include <GLUT/glut.h>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED 1
#include <OpenGL/OpenGLAvailability.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glut.h>
#endif

using namespace Frontier;
using namespace Geek;
using namespace std;

static int powerOfTwo(int input)
{
    int value = 1;

    while (value < input)
    {
        value <<= 1;
    }
    return value;
}

class VideoWidgetRenderer : public Geek::Thread
{
 private:
 public:
    VideoWidgetRenderer();
    virtual ~VideoWidgetRenderer();
};

VideoWidget::VideoWidget(Frontier::FrontierApp* app) : Widget(app, L"Video")
{
    m_mpv = mpv_create();
    m_addedDirect = false;

    int res;
    res = mpv_initialize(m_mpv);
    if (res < 0)
    {
        log(ERROR, "Failed to initialise libmpv!");
        return;
    }

    mpv_request_log_messages(m_mpv, "debug");

glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_texture = 0;

}

VideoWidget::~VideoWidget()
{
}

static void *get_proc_address_mpv(void *fn_ctx, const char *name)
{
    void* addr = dlsym(RTLD_DEFAULT, name);
    printf("XXX: get_proc_address_mpv: %s -> %p\n", name, addr);
    return addr;
}

static void on_mpv_events(void *ctx)
{
    ((VideoWidget*)ctx)->mpvEvent();
}

static void on_mpv_render_update(void *ctx)
{
    ((VideoWidget*)ctx)->mpvRender();
}

void VideoWidget::init()
{
    int advancedControl = 1;

    mpv_opengl_init_params mpvOpenglParams =
    {
        .get_proc_address = get_proc_address_mpv
    };

    mpv_render_param params[] = {
        {MPV_RENDER_PARAM_API_TYPE, (void*)MPV_RENDER_API_TYPE_OPENGL},
        {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, &(mpvOpenglParams)},
        // Tell libmpv that you will call mpv_render_context_update() on render
        // context update callbacks, and that you will _not_ block on the core
        // ever (see <libmpv/render.h> "Threading" section for what libmpv
        // functions you can call at all when this is active).
        // In particular, this means you must call e.g. mpv_command_async()
        // instead of mpv_command().
        // If you want to use synchronous calls, either make them on a separate
        // thread, or remove the option below (this will disable features like
        // DR and is not recommended anyway).
        {MPV_RENDER_PARAM_ADVANCED_CONTROL, &advancedControl},
        {MPV_RENDER_PARAM_INVALID}
    };

    int res;
    res = mpv_render_context_create(&m_mpvGL, m_mpv, params);
    if (res < 0)
    {
        log(ERROR, "Failed to create render contex!");
        return;
    }

    mpv_set_wakeup_callback(m_mpv, on_mpv_events, this);
    mpv_render_context_set_update_callback(m_mpvGL, on_mpv_render_update, this);

}

void VideoWidget::onShow()
{
}

void VideoWidget::calculateSize()
{
    if (!m_addedDirect)
    {
        ((OpenGLEngineWindow*)(getWindow()->getEngineWindow()))->addDirectWidget(this);
        m_addedDirect = true;
    }

    m_minSize.set(100, 100);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
}

bool VideoWidget::draw(Geek::Gfx::Surface* surface)
{
    drawBorder(surface);
    return true;
}

void VideoWidget::setFile(std::string file)
{
    m_file = file;
}

void VideoWidget::play()
{
    if (m_file.length() == 0)
    {
        log(WARN, "play: No file specified!");
        return;
    }

    const char *cmd[] = {"loadfile", m_file.c_str(), "replace", "loop=yes", NULL};
    mpv_command_async(m_mpv, 0, cmd);
}

void VideoWidget::stop()
{

}

void VideoWidget::directBeforeDraw()
{
    BoxModel boxModel = getBoxModel();
    float scale = getWindow()->getScaleFactor();

    Size size = m_setSize;
    size.width -= boxModel.getWidth();
    size.height -= boxModel.getHeight();
    size.width *= scale;
    size.height *= scale;
    log(DEBUG, "directBeforeDraw: Size: %d, %d", size.width, size.height);

    unsigned int textureWidth = powerOfTwo(size.width * scale);
    unsigned int textureHeight = powerOfTwo(size.height * scale);

    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if (m_texture == 0 || m_textureSize.width != textureWidth || m_textureSize.height != textureHeight)
    {
        if (m_texture != 0)
        {
            glDeleteTextures(1, &m_texture);
        }

        glGenTextures(1, &m_texture);
        m_textureSize.width = textureWidth;
        m_textureSize.height = textureHeight;
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);  
    }

    int flipY = 0;
    mpv_opengl_fbo fbo =
    {
        .fbo = (int)m_fbo,
        .w = (int)(m_setSize.width * scale),
        .h = (int)(m_setSize.height * scale),
        .internal_format = 0
    };

    mpv_render_param params[] = {
        // Specify the default framebuffer (0) as target. This will
        // render onto the entire screen. If you want to show the video
        // in a smaller rectangle or apply fancy transformations, you'll
        // need to render into a separate FBO and draw it manually.
        {MPV_RENDER_PARAM_OPENGL_FBO, &fbo},
        // Flip rendering (needed due to flipped GL coordinate system).
        {MPV_RENDER_PARAM_FLIP_Y, &flipY},
        {MPV_RENDER_PARAM_INVALID}
    };

    // See render_gl.h on what OpenGL environment mpv expects, and
    // other API details.

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    mpv_render_context_render(m_mpvGL, params);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glPopAttrib();
}

void VideoWidget::directDraw()
{
    BoxModel boxModel = getBoxModel();
    float scale = getWindow()->getScaleFactor();

    Size size = m_setSize;
    size.width -= boxModel.getWidth();
    size.height -= boxModel.getHeight();
    size.width *= scale;
    size.height *= scale;

    float m_textureCoordX = (float)(size.width ) / (float)m_textureSize.width;
    float m_textureCoordY = (float)(size.height) / (float)m_textureSize.height;

    glPushMatrix();
    glLoadIdentity();

#if 1
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_TRIANGLE_STRIP);
#if 1
    FrontierWindow* window = getWindow();
    Vector2D windowPos = window->getPosition();
    Size screenSize = ((OpenGLEngine*)getApp()->getEngine())->getScreenSize();
    screenSize.width *= scale;
    screenSize.height *= scale;

    Vector2D position = getAbsolutePosition();
    position.x += windowPos.x;
    position.y += windowPos.y;
    position.x += boxModel.getLeft();
    position.y += boxModel.getTop();
    position.x *= scale;
    position.y *= scale;

    //position.y = (screenSize.height * 2) - position.y;

    log(DEBUG, "drawDirect: %d, %d", position.x, position.y);
#else
    Vector2D position(1, 1);
#endif

#if 1

    glTexCoord2f(0, 0);
    glVertex2i(position.x, position.y);

    glTexCoord2f(m_textureCoordX, 0);
    glVertex2i(position.x + (size.width), position.y);

    glTexCoord2f(0, m_textureCoordY);
    glVertex2i(position.x, position.y + (size.height));

    glTexCoord2f(m_textureCoordX, m_textureCoordY);
    glVertex2i(position.x + (size.width), position.y + (size.height));

#endif
#endif
    glEnd();

    glPopMatrix();
}

Widget* VideoWidget::handleEvent(Frontier::Event* event)
{
    return this;
}

void VideoWidget::mpvEvent()
{
    log(DEBUG, "mpvEvent: event!");

    //while (1)
    {
        mpv_event *mp_event = mpv_wait_event(m_mpv, 0);
        switch (mp_event->event_id)
        {
            case MPV_EVENT_NONE:
                return;

            case MPV_EVENT_LOG_MESSAGE:
            {
                mpv_event_log_message *msg = (mpv_event_log_message*)mp_event->data;
                // Print log messages about DR allocations, just to
                // test whether it works. If there is more than 1 of
                // these, it works. (The log message can actually change
                // any time, so it's possible this logging stops working
                // in the future.)
                log(DEBUG, "mpv log: %s", msg->text);
            } break;
            default:
                log(DEBUG, "mpvEvent: unhandled event: %d", mp_event->event_id);
                break;
        }
    }
}

void VideoWidget::mpvRender()
{
    uint64_t flags = mpv_render_context_update(m_mpvGL);

    if ((flags & MPV_RENDER_UPDATE_FRAME) && getWindow() != NULL)
    {
        getWindow()->requestUpdate();
    }
}

