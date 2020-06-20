#ifndef __FRONTIER_WIDGETS_BUTTON_H_
#define __FRONTIER_WIDGETS_BUTTON_H_

#include <frontier/widgets/label.h>

namespace Frontier
{

enum ButtonType
{
    BUTTON_NORMAL,
    BUTTON_TOGGLE
};

/**
 * \brief Simple Button object that response to mouse clicks
 *
 * \ingroup widgets
 */
class Button : public Label
{
 protected:
    ButtonType m_type;
    bool m_emitAll;

 public:
    Button(FrontierApp* ui, std::wstring text, ButtonType type = BUTTON_NORMAL);
    Button(FrontierApp* ui, std::wstring widgetType, std::wstring text, ButtonType type = BUTTON_NORMAL);
    virtual ~Button();

    void setEmitAll(bool emitAll) { m_emitAll = emitAll; }

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
