#ifndef __FRONTIER_WIDGETS_HSV_WHEEL_H_
#define __FRONTIER_WIDGETS_HSV_WHEEL_H_

#include <frontier/widgets.h>
#include <geek/gfx-colour.h>

namespace Frontier
{

/**
 * \brief Displays an HSV colour wheel allowing the user to select colours
 *
 * \ingroup widgets
 */
class HSVWheel : public Widget
{
 private:
    double m_brightness;
    Geek::Gfx::Colour m_colour;

    sigc::signal<void, Geek::Gfx::Colour> m_signalColourChanged;

    bool hsvFromPosition(double* hsv, int x, int y, int cx, int cy, int radius);
    void updateFromMouse(MouseEvent* mouseEvent);

 public:
    HSVWheel(Frontier::FrontierApp* app);
    HSVWheel(Frontier::FrontierApp* app, Geek::Gfx::Colour colour);
    virtual ~HSVWheel();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    sigc::signal<void, Geek::Gfx::Colour> signalColourChanged() { return m_signalColourChanged; };
};

};

#endif
