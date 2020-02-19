#ifndef __FRONTIER_WIDGETS_LABEL_H_
#define __FRONTIER_WIDGETS_LABEL_H_

#include <frontier/widgets.h>

namespace Frontier
{

class Label : public Widget
{
 private:
    std::wstring m_text;
    TextAlign m_align;
    Icon* m_icon;

    int m_lineHeight;

 public:
    Label(FrontierApp* ui, std::wstring text);
    Label(FrontierApp* ui, std::wstring text, TextAlign align);
    Label(FrontierApp* ui, std::wstring text, Icon* icon);
    Label(FrontierApp* ui, std::wstring text, TextAlign align, Icon* icon);
    Label(FrontierWindow* ui, std::wstring text);
    Label(FrontierWindow* ui, std::wstring text, TextAlign align);
    virtual ~Label();

    void setText(std::wstring wtext);
    void setAlign(TextAlign align);
    void setIcon(Icon* icon);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
