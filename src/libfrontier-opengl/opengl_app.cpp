
#include <frontier/engines/opengl.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/tabs.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

OpenGLApp::OpenGLApp() : FrontierApp(L"OpenGL App")
{
    OpenGLEngine* engine = new OpenGLEngine(this);
    engine->setScaleFactor(2);
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

void OpenGLApp::setScreenSize(Size size)
{
    ((OpenGLEngine*)getEngine())->setScreenSize(size);
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    float scale = 2.0;

    Size screenSize = ((OpenGLEngine*)getEngine())->getScreenSize();
    glViewport(0, 0, screenSize.width * scale, screenSize.height * scale);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0.0, (double)screenSize.width * scale, (double)screenSize.height * scale, 0.0, 0.0, 1.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    const std::deque<FrontierWindow*> windows = ((OpenGLEngine*)getEngine())->getWindowOrder();
    for (auto it = windows.rbegin(); it != windows.rend(); it++)
    {
        FrontierWindow* window = *it;
        window->update();
        OpenGLEngineWindow* engineWindow = (OpenGLEngineWindow*)window->getEngineWindow();
        if (engineWindow != NULL)
        {
            engineWindow->update();
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}

void OpenGLApp::mouseMotion(int x, int y)
{
    ((OpenGLEngine*)getEngine())->mouseMotion(x, y);
/*
    MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
    mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;

    Vector2D position = window->getPosition();
    mouseMotionEvent->x = x - position.x;
    mouseMotionEvent->y = y - position.y;
    window->handleEvent(mouseMotionEvent);
*/
}

void OpenGLApp::mouseButton(int x, int y, int button, bool direction)
{
    ((OpenGLEngine*)getEngine())->mouseButton(x, y, button, direction);
/*
    MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
    mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
    mouseButtonEvent->direction = direction;
    mouseButtonEvent->buttons = button;
    mouseButtonEvent->x = x;
    mouseButtonEvent->y = y;
    window->handleEvent(mouseButtonEvent);
*/
}

