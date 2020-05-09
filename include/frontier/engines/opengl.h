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
#include <frontier/engines/windowing.h>

namespace Frontier
{

class OpenGLEngine;

class OpenGLDirectWidget
{
 public:
    OpenGLDirectWidget() {}
    virtual ~OpenGLDirectWidget() {}

    virtual void directBeforeDraw() = 0;
    virtual void directDraw() = 0;
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

};

#endif
