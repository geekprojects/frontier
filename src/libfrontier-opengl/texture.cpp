
#include <frontier/engines/opengl.h>

using namespace Frontier;
using namespace Geek::Gfx;

// Find the smallest power of two that will contain the input
static int powerOfTwo(int input)
{
    int value = 1;

    while (value < input)
    {
        value <<= 1;
    }
    return value;
}

/*
OpenGLTexture::OpenGLTexture(Video* video)
{
    m_video = video;
    m_surface = NULL;

    m_textureValid = false;

    glGenTextures(1, &m_texture);
    glGenSamplers(1, &m_sampler);
}
*/

OpenGLTexture::OpenGLTexture(Surface* surface)
{
    m_surface = surface;

    m_textureValid = false;

printf("OpenGLTexture::OpenGLTexture: this=%p\n", this);
printf("OpenGLTexture::OpenGLTexture: m_texture=%p\n", &m_texture);
    glGenTextures(1, &m_texture);
    glGenSamplers(1, &m_sampler);
}

OpenGLTexture::~OpenGLTexture()
{
    if (m_textureValid)
    {
        glDeleteTextures(1, &m_texture );
    }
}

void OpenGLTexture::bind()
{
    if (!m_textureValid)
    {
        generateTexture();
    }
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindSampler(m_texture, m_sampler);
}

bool OpenGLTexture::generateTexture()
{
    unsigned int texWidth = powerOfTwo(m_surface->getWidth());
    unsigned int texHeight = powerOfTwo(m_surface->getHeight());
printf("OpenGLTexture::generateTexture: surface: %d, %d, texture: %d, %d\n", m_surface->getWidth(), m_surface->getHeight(), texWidth, texHeight);

    if (texWidth != m_surface->getWidth() ||
        texHeight != m_surface->getHeight())
    {
        printf("OpenGLTexture::generateTexture: TODO: Handle non-power-of-two surface size\n");
        return true;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        4,
        texWidth, texHeight,
        0,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        m_surface->getData());

    m_textureValid = true;
    return true;
}

