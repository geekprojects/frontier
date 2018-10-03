#ifndef __FRONTIER_WIDGETS_SCROLLBAR_H_
#define __FRONTIER_WIDGETS_SCROLLBAR_H_

#include <frontier/widgets.h>

namespace Frontier
{

class ScrollBar : public Widget
{
 private:
    int m_min;
    int m_max;
    int m_pos;
    int m_size;
    bool m_dragging;

    int getControlPos();
    int getControlSize();
    int range() { return m_max - (m_min + m_size); }

    sigc::signal<void, int> m_changedPositionSignal;

 public:
    ScrollBar(FrontierApp* ui);
    ScrollBar(FrontierWindow* window);
    virtual ~ScrollBar();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void set(int min, int max, int size);
    void setPos(int pos);
    int getPos();

    virtual sigc::signal<void, int> changedPositionSignal() { return m_changedPositionSignal; }
};

};

#endif
