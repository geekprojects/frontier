#ifndef __FRONTIER_WIDGETS_LABEL_H_
#define __FRONTIER_WIDGETS_LABEL_H_

#include <frontier/widgets.h>

namespace Frontier
{

/**
 * \brief Simple Widget for displaying text with optional Icon
 *
 * Other Widgets can inherit from Label to provide basic text formatting.
 *
 * \ingroup widgets
 *
 */
class Label : public Widget
{
 private:
    std::wstring m_text;
    TextAlign m_align;
    Icon* m_icon;

    int m_lineHeight;

 public:
    Label(FrontierApp* ui, std::wstring widgetName, std::wstring text);
    Label(FrontierApp* ui, std::wstring text);
    Label(FrontierApp* ui, std::wstring text, TextAlign align);
    Label(FrontierApp* ui, std::wstring text, Icon* icon);
    Label(FrontierApp* ui, std::wstring text, TextAlign align, Icon* icon);
    virtual ~Label();

    void setText(std::wstring wtext);
    std::wstring getText() { return m_text; }
    void setAlign(TextAlign align);
    void setIcon(Icon* icon);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
