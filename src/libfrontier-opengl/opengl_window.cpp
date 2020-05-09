
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
            log(DEBUG, "update: Recreating surface: %d, %d != %d, %d",  m_textureSurface->getWidth(), m_textureSurface->getHeight(), textureWidth, textureHeight);
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
        log(DEBUG, "update: fwidget=%p, visible=%d", fwidget, fwidget->isVisible());
        if (fwidget->isVisible())
        {
            widget->directDraw();
        }
    }
    glBindTexture(GL_TEXTURE_2D, m_texture);

    return true;
}

