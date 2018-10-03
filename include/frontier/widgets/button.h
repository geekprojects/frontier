#ifndef __FRONTIER_WIDGETS_BUTTON_H_
#define __FRONTIER_WIDGETS_BUTTON_H_

#include <frontier/widgets.h>

namespace Frontier
{

class Button : public Widget
{
 protected:
    std::wstring m_text;
    bool m_state;

    sigc::signal<void> m_clickSignal;

 public:
    Button(FrontierApp* ui, std::wstring text);
    Button(FrontierWindow* ui, std::wstring text);
    virtual ~Button();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    virtual sigc::signal<void> clickSignal() { return m_clickSignal; }
};

};

#endif
