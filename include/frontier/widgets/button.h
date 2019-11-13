#ifndef __FRONTIER_WIDGETS_BUTTON_H_
#define __FRONTIER_WIDGETS_BUTTON_H_

#include <frontier/widgets.h>

namespace Frontier
{

class Button : public Widget
{
 protected:
    std::wstring m_text;

 public:
    Button(FrontierApp* ui, std::wstring text);
    Button(FrontierWindow* ui, std::wstring text);
    Button(FrontierApp* ui, std::wstring widgetType, std::wstring text);
    Button(FrontierWindow* ui, std::wstring widgetType, std::wstring text);
    virtual ~Button();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
