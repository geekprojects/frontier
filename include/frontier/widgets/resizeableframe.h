#ifndef __FRONTIER_WIDGETS_RESIZEABLE_FRAME_H_
#define __FRONTIER_WIDGETS_RESIZEABLE_FRAME_H_

#include <frontier/widgets/frame.h>

namespace Frontier
{

class ResizeableFrame : public Frame
{
 protected:
    std::vector<float> m_sizes;

    // Dragging resize state
    bool m_dragging;
    int m_dragWidget;
    int m_dragPos;

    virtual void layout();

 public:
    ResizeableFrame(FrontierApp* ui, bool horizontal);
    ResizeableFrame(FrontierWindow* ui, bool horizontal);
    virtual ~ResizeableFrame();

    virtual void add(Widget* widget);
    virtual void addWithSize(Widget* widget, int setPc);

    virtual Widget* handleMessage(Frontier::Message* msg);

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_RESIZE_HORIZONTAL; }
};

};

#endif
