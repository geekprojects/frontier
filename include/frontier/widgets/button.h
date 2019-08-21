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
    bool m_highlight;

    sigc::signal<void, Button*> m_clickSignal;

 public:
    Button(FrontierApp* ui, std::wstring text);
    Button(FrontierWindow* ui, std::wstring text);
    virtual ~Button();

    void setHighlight(bool highlight);
    bool getHighlight() { return m_highlight; }

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual sigc::signal<void, Button*> clickSignal() { return m_clickSignal; }
};

};

#endif
