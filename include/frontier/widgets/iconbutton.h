#ifndef __FRONTIER_WIDGETS_ICON_BUTTON_H_
#define __FRONTIER_WIDGETS_ICON_BUTTON_H_

#include <frontier/widgets/button.h>

namespace Frontier
{

class IconButton : public Button
{
 private:
    wchar_t m_icon;

 public:
    IconButton(FrontierApp* ui, wchar_t icon);
    IconButton(FrontierWindow* ui, wchar_t icon);
    virtual ~IconButton();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
