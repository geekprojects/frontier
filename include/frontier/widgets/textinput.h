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
    unsigned int m_offsetX;
    unsigned int m_maxLength;

    std::vector<int> m_charX;

    bool m_selecting;
    int m_selectStart;
    int m_selectEnd;

    void drawCursor(Geek::Gfx::Surface* surface, int x, int y);

    int charAt(int x);

    Geek::Gfx::Surface* m_textSurface;

    sigc::signal<void, TextInput*> m_signalEditingEnd;
    sigc::signal<void, TextInput*> m_signalTextChanged;

 public:
    TextInput(FrontierApp* ui);
    TextInput(FrontierApp* ui, std::wstring text);
    TextInput(FrontierWindow* ui);
    TextInput(FrontierWindow* ui, std::wstring text);
    virtual ~TextInput();

    void setMaxLength(unsigned int maxLen)
    {
        m_maxLength = maxLen;
    }

    void setText(std::wstring wtext);
    std::wstring getText() { return m_text; }

    bool hasSelection()
    {
        return (m_selectStart >= 0 && m_selectStart != m_selectEnd);
    }
    std::wstring getSelected();
    std::wstring cutSelected();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);

    virtual Frontier::WindowCursor getCursor() { return Frontier::CURSOR_EDIT; }

    virtual bool isValid(std::wstring str);

    sigc::signal<void, TextInput*> signalEditingEnd() { return m_signalEditingEnd; }
    sigc::signal<void, TextInput*> signalTextChanged() { return m_signalTextChanged; }
};

};

#endif
