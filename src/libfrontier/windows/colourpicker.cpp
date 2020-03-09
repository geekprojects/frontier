
#include <frontier/windows/colourpicker.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/label.h>
#include <frontier/fontawesome.h>

using namespace Geek;
using namespace Geek::Gfx;
using namespace Frontier;
using namespace std;

ColourPickerWindow::ColourPickerWindow(Colour colour)
{
    m_colour = colour;
}


ColourPickerWindow::~ColourPickerWindow()
{
}

FrontierColourPickerWindow::FrontierColourPickerWindow(Frontier::FrontierApp* app)
    : ColourPickerWindow(Colour(255, 255, 255)), FrontierWindow(app, L"Colour Picker", WINDOW_NORMAL)
{
}

FrontierColourPickerWindow::FrontierColourPickerWindow(Frontier::FrontierApp* app, Colour colour)
    : ColourPickerWindow(colour), FrontierWindow(app, L"Colour Picker", WINDOW_NORMAL)
{
}


FrontierColourPickerWindow::~FrontierColourPickerWindow()
{
    log(DEBUG, "~ColourPickerWindow: Deleting!");
}

bool FrontierColourPickerWindow::init()
{
    Frame* root = new Frame(this, false);
    root->setWidgetClass(L"colourPicker");

    m_hsvWheel = new HSVWheel(getApp(), m_colour);
    root->add(m_hsvWheel);

    setContent(root);

    update();

    return true;
}

bool FrontierColourPickerWindow::update()
{
    return true;
}


