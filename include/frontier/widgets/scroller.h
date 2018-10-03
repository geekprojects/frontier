#ifndef __FRONTIER_WIDGETS_SCROLLER_H_
#define __FRONTIER_WIDGETS_SCROLLER_H_

#include <frontier/widgets.h>
#include <frontier/widgets/scrollbar.h>

namespace Frontier
{

class Scroller : public Widget
{
 private:

    ScrollBar* m_scrollBar;
    Widget* m_child;
    Geek::Gfx::Surface* m_childSurface;

    void checkSurfaceSize(bool highDPI);
    int getWidthOverhead() { return (m_scrollBar->getWidth() - 2); }

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

    int getPos() { return m_scrollBar->getPos(); }

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void setChild(Widget* child);
};

};

#endif
