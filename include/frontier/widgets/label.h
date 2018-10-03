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

    int m_lineHeight;

 public:
    Label(FrontierApp* ui, std::wstring text);
    Label(FrontierApp* ui, std::wstring text, TextAlign align);
    Label(FrontierWindow* ui, std::wstring text);
    Label(FrontierWindow* ui, std::wstring text, TextAlign align);
    virtual ~Label();

    void setText(std::wstring wtext);
    void setAlign(TextAlign align);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

};

#endif
