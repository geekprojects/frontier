
#include <frontier/engines/opengl.h>

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

    unsigned int textureWidth = powerOfTwo(size.width);
    unsigned int textureHeight = powerOfTwo(size.height);
    m_textureCoordX = (float)size.width / (float)textureWidth;
    m_textureCoordY = (float)size.height / (float)textureHeight;

    if (m_textureSurface == NULL || m_textureSurface->getWidth() != textureWidth || m_textureSurface->getHeight() != textureHeight)
    {
            m_textureSurface = new HighDPISurface(textureWidth, textureHeight, 4);
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
    glVertex2i(position.x + (size.width * 2), position.y);

    glTexCoord2f(0, m_textureCoordY);
    glVertex2i(position.x, position.y + (size.height * 2));

    glTexCoord2f(m_textureCoordX, m_textureCoordY);
    glVertex2i(position.x + (size.width * 2), position.y + (size.height * 2));

    glEnd();

    return true;
}

