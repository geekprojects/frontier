
#include <frontier/engines/opengl.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

OpenGLDirectWidget::OpenGLDirectWidget(FrontierApp* ui, wstring name) : Widget(ui, name)
{
}

void OpenGLDirectWidget::setViewport()
{
#if 1
    BoxModel boxModel = getBoxModel();
    FrontierWindow* window = getWindow();
    float scale = window->getScaleFactor();
    Vector2D windowPos;// = window->getPosition();

    Size size = m_setSize;
    size.width -= boxModel.getWidth();
    size.height -= boxModel.getHeight();
    size.width *= scale;
    size.height *= scale;

    Vector2D position = getAbsolutePosition();
    position.x += windowPos.x;
    position.y += windowPos.y;
    position.x += boxModel.getLeft();
    position.y += boxModel.getTop();
    position.x *= scale;
    position.y *= scale;

    Size screenSize = ((OpenGLEngine*)getApp()->getEngine())->getScreenSize();
    //screenSize.width *= scale;
    screenSize.height *= scale;
    position.y = (screenSize.height) - (position.y + size.height);

    glViewport(position.x, position.y, size.width, size.height);
#endif
    //Size screenSize = ((OpenGLEngine*)getApp()->getEngine())->getScreenSize();
//glViewport(0, screenSize.height, 100, 100);
//glViewport(0, 0, 100, 100);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();	

gluPerspective( 45.0, (GLfloat)(size.width)/(GLfloat)(size.height), 0.1f, 500.0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

