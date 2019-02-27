
#include <frontier/icon.h>
#include <frontier/theme.h>

using namespace std;
using namespace Frontier;

Icon::Icon(UITheme* theme)
{
    m_theme = theme;
}

Icon::~Icon()
{
}

TextIcon::TextIcon(UITheme* theme, uint32_t icon) : Icon(theme)
{
    m_icon = icon;
}

TextIcon::~TextIcon()
{
}

Size TextIcon::getSize()
{
    Size size;
    size.width = m_theme->getIconWidth(m_icon);
    size.height = m_theme->getIconHeight();
    return size;
}

void TextIcon::draw(Geek::Gfx::Surface* surface, int x, int y)
{
    m_theme->drawIcon(surface, x, y, m_icon, false);
}

SurfaceIcon::SurfaceIcon(UITheme* theme, Geek::Gfx::Surface* surface) : Icon(theme)
{
    m_surface = surface;
    m_scaledSurface = NULL;
}

SurfaceIcon::~SurfaceIcon()
{
}

Size SurfaceIcon::getSize()
{
    Size size;
    //size.width = m_theme->getIconWidth(m_icon);
    size.width = m_theme->getIconHeight();
    size.height = m_theme->getIconHeight();
    return size;
}

void SurfaceIcon::draw(Geek::Gfx::Surface* surface, int x, int y)
{
if (m_scaledSurface == NULL)
{
    bool highDPI = surface->isHighDPI();
    Size size = getSize();
    if (highDPI)
    {
        size.width *= 2;
        size.height *= 2;
    }

    //if (m_surface->getWidth() != (uint32_t)size.width || m_surface->getHeight() != (uint32_t)size.height)
    {
        printf("SurfaceIcon::draw: Resizing to: %d, %d\n", size.width, size.height);
        m_scaledSurface = m_surface->scaleToFit(size.width, size.height);
    }
}

    surface->blit(x, y, m_scaledSurface, true);
}

