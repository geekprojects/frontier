#ifndef __FRONTIER_WIDGETS_HSV_WHEEL_H_
#define __FRONTIER_WIDGETS_HSV_WHEEL_H_

#include <frontier/widgets.h>
#include <geek/gfx-colour.h>

namespace Frontier
{

class HSVWheel : public Widget
{
 private:
    Geek::Gfx::Colour m_colour;

    sigc::signal<void, Colour> m_signalColourChanged;

    bool hsvFromPosition(double* hsv, int x, int y, int cx, int cy, int radius);

 public:
    HSVWheel(Frontier::FrontierApp* app);
    virtual ~HSVWheel();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    sigc::signal<void, Colour> signalColourChanged() { return m_signalColourChanged; };
};

};

#endif
