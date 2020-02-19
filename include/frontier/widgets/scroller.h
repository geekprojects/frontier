#ifndef __FRONTIER_WIDGETS_SCROLLER_H_
#define __FRONTIER_WIDGETS_SCROLLER_H_

#include <frontier/widgets.h>
#include <frontier/widgets/scrollbar.h>

namespace Frontier
{

/**
 * \brief A Widget that provides a view of a larger Widget hierarchy
 *
 * \ingroup widgets
 */
class Scroller : public Widget
{
 private:
    ScrollBar* m_hScrollBar;
    ScrollBar* m_vScrollBar;
    Widget* m_child;
    Geek::Gfx::Surface* m_childSurface;
    Size m_drawSize;

    void checkSurfaceSize(bool highDPI);
    int getWidthOverhead() { return (m_vScrollBar->getWidth() - 2); }

    void initScroller(Widget* child);

 public:
    Scroller(FrontierApp* ui);
    Scroller(FrontierApp* ui, Widget* child);
    Scroller(FrontierWindow* ui);
    Scroller(FrontierWindow* ui, Widget* child);
    virtual ~Scroller();

    virtual void calculateSize();
    virtual void layout();
    //virtual void setWidth(int width);

    int getPos() { return m_vScrollBar->getPos(); }

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void setChild(Widget* child);

    virtual void dump(int level);
};

};

#endif
