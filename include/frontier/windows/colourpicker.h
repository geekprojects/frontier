#ifndef __FRONTIER_WINDOWS_COLOUR_PICKER_H_
#define __FRONTIER_WINDOWS_COLOUR_PICKER_H_

#include <frontier/window.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/hsvwheel.h>

namespace Frontier
{


/**
 * \brief Colour Picker Window
 *
 * Allows a user to select a colour
 *
 * \ingroup windows
 */
class ColourPickerWindow
{
 protected:
    Geek::Gfx::Colour m_colour;

    sigc::signal<void, Geek::Gfx::Colour> m_colourSelectedSignal;

 public:
    ColourPickerWindow(Geek::Gfx::Colour colour);
    virtual ~ColourPickerWindow();

    sigc::signal<void, Geek::Gfx::Colour> colourSelectedSignal() { return m_colourSelectedSignal; }

    virtual void show() {}
};

class FrontierColourPickerWindow : public ColourPickerWindow, public Frontier::FrontierWindow
{
 private:
    HSVWheel* m_hsvWheel;

    void onCloseButton(Widget* widget);
    void onHSVColourChange(Geek::Gfx::Colour);

 public:
    FrontierColourPickerWindow(Frontier::FrontierApp* app);
    FrontierColourPickerWindow(Frontier::FrontierApp* app, Geek::Gfx::Colour colour);
    virtual ~FrontierColourPickerWindow();

    bool init();
    bool update();
    void show();
};

};

#endif
