#ifndef __FRONTIER_WIDGETS_SCROLLBAR_H_
#define __FRONTIER_WIDGETS_SCROLLBAR_H_

#include <frontier/widgets.h>

namespace Frontier
{

/**
 * \brief A simple scroll bar Widget
 *
 * \ingroup widgets
 */
class ScrollBar : public Widget
{
 private:
    bool m_horizontal;
    int m_min;
    int m_max;
    int m_pos;
    int m_size;
    bool m_dragging;
    int m_dragOffset;

    int getScaledValue(BoxModel& boxModel, int v);
    int getControlPos(BoxModel& boxModel);
    int getControlSize(BoxModel& boxModel);
    int range() { return m_max - (m_min + m_size); }

    sigc::signal<void, int> m_changedPositionSignal;

 public:
    ScrollBar(FrontierApp* ui, bool horizontal);
    ScrollBar(FrontierWindow* window, bool horizontal);
    virtual ~ScrollBar();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void set(int min, int max, int size);
    void setPos(int pos);
    int getPos();

    virtual sigc::signal<void, int> changedPositionSignal() { return m_changedPositionSignal; }
};

};

#endif
