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
#include <frontier/embedded.h>

namespace Frontier
{

class OpenGLEngineWindow : public Frontier::EmbeddedWindow
{
 protected:
    unsigned int m_texture;
    unsigned int m_sampler;
    float m_textureCoordX;
    float m_textureCoordY;
    bool m_textureValid;
    Geek::Gfx::Surface* m_textureSurface;

 public:
    OpenGLEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~OpenGLEngineWindow();

    virtual bool init();

    virtual bool update();
};

/**
 * \brief An Engine designed for embedding Frontier UIs in to OpenGL applications
 *
 * \ingroup engines
 */
class OpenGLApp : public Frontier::FrontierApp
{
 protected:
    Size m_screenSize;

 public:
    OpenGLApp();
    virtual ~OpenGLApp();

    virtual bool init();

    void setScreenSize(Size size) { m_screenSize = size; }

    void mouseMotion(Frontier::FrontierWindow* window, int x, int y);
    void mouseButton(Frontier::FrontierWindow* window, int x, int y, int button, bool direction);

    virtual void draw();
};

class OpenGLEngine : public EmbeddedEngine
{
 protected:

 public:
    OpenGLEngine(FrontierApp* app);
    virtual ~OpenGLEngine();

    virtual bool initWindow(FrontierWindow* window);
};

};

#endif
