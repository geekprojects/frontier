#ifndef __FRONTIER_WIDGETS_FRAME_H_
#define __FRONTIER_WIDGETS_FRAME_H_

#include <frontier/widgets.h>

namespace Frontier
{

class Frame : public Widget
{
 protected:
    bool m_horizontal;
    bool m_border;

    virtual void calculateSize();
    virtual void layout();

 public:
    Frame(FrontierApp* ui, bool horizontal);
    Frame(FrontierApp* ui, std::wstring widgetName, bool horizontal);
    Frame(FrontierWindow* ui, bool horizontal);
    Frame(FrontierWindow* ui, std::wstring widgetName, bool horizontal);
    virtual ~Frame();

    void setBorder(bool border) { m_border = border; }

    virtual void add(Widget* widget);

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);
};

class HFrame : public Frame
{
 public:
    HFrame(FrontierApp* ui);
    HFrame(FrontierWindow* ui);
    virtual ~HFrame();
};

class VFrame : public Frame
{
 public:
    VFrame(FrontierApp* ui);
    VFrame(FrontierWindow* ui);
    virtual ~VFrame();
};

};

#endif
