#ifndef __FRONTIER_WIDGETS_BUTTON_H_
#define __FRONTIER_WIDGETS_BUTTON_H_

#include <frontier/widgets.h>

namespace Frontier
{

enum ButtonType
{
    BUTTON_NORMAL,
    BUTTON_TOGGLE
};

/**
 * \brief Simple button object that response to mouse clicks
 *
 * \ingroup widgets
 */
class Button : public Widget
{
 protected:
    ButtonType m_type;
    std::wstring m_text;

 public:
    Button(FrontierApp* ui, std::wstring text, ButtonType type = BUTTON_NORMAL);
    Button(FrontierWindow* ui, std::wstring text, ButtonType type = BUTTON_NORMAL);
    Button(FrontierApp* ui, std::wstring widgetType, std::wstring text, ButtonType type = BUTTON_NORMAL);
    Button(FrontierWindow* ui, std::wstring widgetType, std::wstring text, ButtonType type = BUTTON_NORMAL);
    virtual ~Button();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
