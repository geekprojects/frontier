#ifndef __FRONTIER_WIDGETS_FRAME_H_
#define __FRONTIER_WIDGETS_FRAME_H_

#include <frontier/widgets.h>

namespace Frontier
{

/**
 * \brief Groups widgets together vertically or horizontally
 *
 * \ingroup widgets
 */
class Frame : public Widget
{
 protected:
    bool m_horizontal;

 public:
    Frame(FrontierApp* ui, bool horizontal);
    Frame(FrontierApp* ui, std::wstring widgetName, bool horizontal);
    Frame(FrontierWindow* ui, bool horizontal);
    Frame(FrontierWindow* ui, std::wstring widgetName, bool horizontal);
    virtual ~Frame();

    virtual void add(Widget* widget);
    virtual void remove(Widget* widget);

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

/**
 * \brief Groups widgets together horizontally
 *
 * \ingroup widgets
 */
class HFrame : public Frame
{
 public:
    HFrame(FrontierApp* ui);
    HFrame(FrontierWindow* ui);
    virtual ~HFrame();
};

/**
 * \brief Groups widgets together vertically
 *
 * \ingroup widgets
 */
class VFrame : public Frame
{
 public:
    VFrame(FrontierApp* ui);
    VFrame(FrontierWindow* ui);
    virtual ~VFrame();
};

};

#endif
