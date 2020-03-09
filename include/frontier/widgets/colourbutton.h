#ifndef __FRONTIER_WIDGETS_COLOUR_BUTTON_H_
#define __FRONTIER_WIDGETS_COLOUR_BUTTON_H_

#include <frontier/widgets/button.h>
#include <frontier/windows/colourpicker.h>
#include <geek/gfx-colour.h>

namespace Frontier
{

class ColourButton : public Frontier::Button
{
 private:
    Icon* m_colourIcon;
    Geek::Gfx::Colour m_colour;
    ColourPickerWindow* m_colourPicker;

    sigc::signal<void, Geek::Gfx::Colour> m_colourSelectedSignal;

    void setup();

    void onClick(Widget* widget);

 public:
    ColourButton(FrontierApp* app);
    ColourButton(FrontierApp* app, Geek::Gfx::Colour colour);
    virtual ~ColourButton();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    void setColour(Geek::Gfx::Colour colour);

    sigc::signal<void, Geek::Gfx::Colour> colourSelectedSignal() { return m_colourSelectedSignal; }
};

};

#endif
