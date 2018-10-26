#ifndef __FRONTIER_WIDGETS_INPUT_H_
#define __FRONTIER_WIDGETS_INPUT_H_

#include <frontier/widgets.h>

namespace Frontier
{

class TextInput : public Widget
{
 private:
    std::wstring m_text;
    unsigned int m_column;

    void drawCursor(Geek::Gfx::Surface* surface, int x, int y);

 public:
    TextInput(FrontierApp* ui);
    TextInput(FrontierApp* ui, std::wstring text);
    TextInput(FrontierWindow* ui);
    TextInput(FrontierWindow* ui, std::wstring text);
    virtual ~TextInput();

    void setText(std::wstring wtext);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

};

#endif
