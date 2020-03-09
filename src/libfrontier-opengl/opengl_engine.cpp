
#include <frontier/opengl.h>

using namespace Frontier;

OpenGLEngine::OpenGLEngine(FrontierApp* app) : EmbeddedEngine(app)
{
}

OpenGLEngine::~OpenGLEngine()
{
}

bool OpenGLEngine::initWindow(FrontierWindow* window)
{
    OpenGLEngineWindow* ew = new OpenGLEngineWindow(this, window);
    ew->init();
    window->setEngineWindow(ew);
    return true;
}


