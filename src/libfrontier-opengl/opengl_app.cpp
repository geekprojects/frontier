
#include <frontier/opengl.h>
#include <frontier/embedded.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/tabs.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

OpenGLApp::OpenGLApp() : FrontierApp(L"OpenGL App")
{
    EmbeddedEngine* engine = new EmbeddedEngine(this);
    setEngine(engine);
}

OpenGLApp::~OpenGLApp()
{
}

bool OpenGLApp::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    return true;
}

void OpenGLApp::draw()
{
    // Enter 2D mode
    glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* This allows alpha blending of 2D textures with the scene */
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    glViewport(0, 0, m_screenSize.width, m_screenSize.height);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0.0, (double)m_screenSize.width, (double)m_screenSize.height, 0.0, 0.0, 1.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    vector<FrontierWindow*> windows = getWindows();
    for (FrontierWindow* window : windows)
    {
        OpenGLWindow* engineWindow = (OpenGLWindow*)window;
        if (engineWindow != NULL)
        {
            engineWindow->draw();
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}

void OpenGLApp::mouseMotion(FrontierWindow* window, int x, int y)
{
    MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
    mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;
    mouseMotionEvent->x = x;
    mouseMotionEvent->y = y;
    window->handleEvent(mouseMotionEvent);
}

void OpenGLApp::mouseButton(Frontier::FrontierWindow* window, int x, int y, int button, bool direction)
{
    MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
    mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
    mouseButtonEvent->direction = direction;
    mouseButtonEvent->buttons = button;
    mouseButtonEvent->x = x;
    mouseButtonEvent->y = y;
    window->handleEvent(mouseButtonEvent);
}

