
#include <frontier/widgets/colourbutton.h>
#include <frontier/fontawesome.h>

#include <math.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

ColourButton::ColourButton(FrontierApp* app) : Button(app, L"ColourButton", L"")
{
    m_colour = Colour(255, 255, 255);

    setup();
}

ColourButton::ColourButton(FrontierApp* app, Geek::Gfx::Colour colour) : Button(app, L"ColourButton", L"")
{
    m_colour = colour;

    setup();
}

ColourButton::~ColourButton()
{
}

void ColourButton::setup()
{
    m_colourIcon = getApp()->getTheme()->getIcon(FRONTIER_ICON_PALETTE);
    m_colourPicker = NULL;

    clickSignal().connect(sigc::mem_fun(*this, &ColourButton::onClick));
}

void ColourButton::calculateSize()
{
    BoxModel boxModel = getBoxModel();
    Size iconSize = m_colourIcon->getSize();

    m_minSize.width = boxModel.getWidth() + (iconSize.width * 3) + boxModel.marginLeft;
    m_minSize.height = boxModel.getHeight() + iconSize.height;

    m_maxSize.width = m_minSize.width;
    m_maxSize.height = m_minSize.height;
}

bool ColourButton::draw(Surface* surface)
{
    BoxModel boxModel = getBoxModel();
    drawBorder(surface);

    int colWidth = ((surface->getWidth() - (boxModel.getWidth() + boxModel.marginLeft)) / 3) * 2;
    int colHeight = (surface->getHeight() - boxModel.getHeight());

    surface->drawRectFilled(boxModel.getLeft(), boxModel.getTop(), colWidth, colHeight, m_colour.getInt32());

    m_colourIcon->draw(surface, (colWidth ) + boxModel.getLeft() + boxModel.marginLeft, boxModel.getTop());

    return true;
}

void ColourButton::onClick(Widget* widget)
{
    if (m_colourPicker != NULL)
    {
        return;
    }

    m_colourPicker = getApp()->openColourPickerWindow(m_colour);
m_colourPicker->colourSelectedSignal().connect(sigc::mem_fun(*this, &ColourButton::setColour));
}

void ColourButton::setColour(Colour colour)
{
    m_colour = colour;
    setDirty(DIRTY_CONTENT);

    getWindow()->requestUpdate();
}

