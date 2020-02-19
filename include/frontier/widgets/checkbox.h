#ifndef __FRONTIER_WIDGETS_CHECK_BOX_H_
#define __FRONTIER_WIDGETS_CHECK_BOX_H_

#include <frontier/widgets/button.h>
#include <frontier/fontawesome.h>

namespace Frontier
{

/**
 * \brief A Button Widget that displays a Tick/Check when selected
 *
 * \ingroup widgets
 */
class CheckBox : public Button
{
 private:
    Icon* m_icon;

 public:
    CheckBox(FrontierApp* app);
    virtual ~CheckBox();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
