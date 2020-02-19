#ifndef __FRONTIER_ICON_H_
#define __FRONTIER_ICON_H_

#include <stdint.h>
#include <frontier/object.h>
#include <frontier/fontawesome.h>
#include <frontier/utils.h>
#include <geek/gfx-surface.h>

namespace Frontier
{

class UITheme;

/**
 * \defgroup icons Graphical icons
 */

/**
 * \brief A base class for graphical icons
 *
 * \ingroup icons
 */
class Icon : public FrontierObject
{
 protected:
    UITheme* m_theme;
    
 public:
    Icon(UITheme* theme);
    virtual ~Icon();

    virtual Size getSize() = 0;
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y) = 0;
};

/**
 * \brief An Icon implemented with FontAwesome
 *
 * \ingroup icons
 */
class TextIcon : public Icon
{
 private:
    uint32_t m_icon;

 public:
    TextIcon(UITheme* theme, uint32_t icon);
    virtual ~TextIcon();

    virtual Size getSize();
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y);
};

/**
 * \brief An Icon implemented with a libgeek Surface
 *
 * \ingroup icons
 */
class SurfaceIcon : public Icon
{
 private:
    Geek::Gfx::Surface* m_surface;
    Geek::Gfx::Surface* m_scaledSurface;

 public:
    SurfaceIcon(UITheme* theme, Geek::Gfx::Surface* surface);
    virtual ~SurfaceIcon();

    virtual Size getSize();
    virtual void draw(Geek::Gfx::Surface* surface, int x, int y);
};

};

#endif
