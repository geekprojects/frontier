#ifndef __FRONTIER_WIDGETS_ICON_BUTTON_H_
#define __FRONTIER_WIDGETS_ICON_BUTTON_H_

#include <frontier/widgets/button.h>
#include <frontier/fontawesome.h>
#include <frontier/icon.h>

namespace Frontier
{

class IconButton : public Button
{
 private:
    Icon* m_icon;

 public:
    IconButton(FrontierApp* ui, Icon* icon);
    IconButton(FrontierWindow* ui, Icon* icon);
    virtual ~IconButton();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
