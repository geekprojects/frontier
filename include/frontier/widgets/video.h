#ifndef __CONTROL_PANEL_VIDEO_WIDGET_H_
#define __CONTROL_PANEL_VIDEO_WIDGET_H_

#include <frontier/widgets.h>
#include <frontier/engines/opengl.h>
#include <mpv/client.h>
#include <mpv/render_gl.h>

class VideoWidget : public Frontier::Widget, public Frontier::OpenGLDirectWidget
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
