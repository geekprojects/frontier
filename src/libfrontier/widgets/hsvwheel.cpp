
#include <frontier/widgets/hsvwheel.h>

#include <math.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

HSVWheel::HSVWheel(FrontierApp* app) : Widget(app, L"HSVWheel")
{
    m_colour = Colour(255, 255, 255);
}

HSVWheel::~HSVWheel()
{
}


void HSVWheel::calculateSize()
{
    m_minSize.width = 100;
    m_minSize.height = 100;

    m_maxSize.width = 200;
    m_maxSize.height = 200;
}

bool HSVWheel::draw(Geek::Gfx::Surface* surface)
{
    drawBorder(surface);

    BoxModel boxModel = getBoxModel();
    int width = surface->getWidth() - boxModel.getWidth();
    int height = surface->getHeight() - boxModel.getHeight();

    int drawX = boxModel.getLeft();
    int drawY = boxModel.getTop();
    HighDPISurface* highDPISurface = NULL;
    if (surface->isHighDPI())
    {
        width *= 2;
        height *= 2;
        highDPISurface = (HighDPISurface*)surface->getRoot();

        Geek::Rect r = surface->absolute();
        drawX += r.x;
        drawY += r.y;
        drawX *= 2;
        drawY *= 2;
    }

    int cx = width / 2;
    int cy = height / 2;

    int radius = cx;
    if (cy < radius)
    {
        radius = cy;
    }

    int y;
    for (y = 0; y < height; y++)
    {
        int x;
        for (x = 0; x < width; x++)
        {
            double hsv[3];
            bool inside = hsvFromPosition(hsv, x, height - y, cx, cy, radius);
            if (inside)
            {
                hsv[0] -= 2.0 / 6.0;
                Colour c = Colour::fromHSB(hsv[0], hsv[1], hsv[2]);

                if (surface->isHighDPI())
                {
                    highDPISurface->drawSubPixel(x + drawX, y + drawY, c.getInt32());
                }
                else
                {
                    surface->drawPixel(x + drawX, y + drawY, c.getInt32());
                }
            }
        }
    }

    double selectedHSV[3];
    m_colour.toHSB(selectedHSV);

    double angle = selectedHSV[0] * (2 * M_PI); // Convert to radians
    double distr = (double)radius * selectedHSV[1];
    log(DEBUG, "draw: angle=%0.2f, distr=%0.2f", angle, distr);

    int selectedX = (int)(distr * cos(angle)) + cx;
    int selectedY = cy - (int)(distr * sin(angle));

    if (surface->isHighDPI())
    {
        selectedX /= 2;
        selectedY /= 2;
    }

    selectedX += boxModel.getLeft();
    selectedY += boxModel.getTop();

    surface->drawCircleFilled(selectedX, selectedY, 4, 0xff000000);
    surface->drawCircleFilled(selectedX, selectedY, 2, 0xffffffff);

    return true;
}

Widget* HSVWheel::handleEvent(Frontier::Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            updateFromMouse(mouseButtonEvent);

            m_selected = mouseButtonEvent->direction;
        } break;

        case FRONTIER_EVENT_MOUSE_MOTION:
            if (m_selected)
            {
                updateFromMouse((MouseEvent*)event);
            }
            break;

        default:
            // Ignore
            break;
}


    return this;
}

void HSVWheel::updateFromMouse(MouseEvent* mouseEvent)
{
    BoxModel boxModel = getBoxModel();

    int cx = (m_setSize.width - boxModel.getWidth()) / 2;
    int cy = (m_setSize.height - boxModel.getHeight()) / 2;
    int radius = cx;
    if (cy < radius)
    {
        radius = cy;
    }

    Vector2D thisPos = getAbsolutePosition();
    int x = mouseEvent->x - thisPos.x;
    int y = mouseEvent->y - thisPos.y;
    x -= boxModel.getLeft();
    y -= boxModel.getRight();

    double hsb[3];
    bool inside = hsvFromPosition(hsb, x, y, cx, cy, radius);
    if (inside)
    {
        m_colour = Colour::fromHSB(hsb[0], hsb[1], hsb[2]);
        log(DEBUG, "handleEvent: colour: %d, %d, %d", m_colour.r, m_colour.g, m_colour.b);
        setDirty(DIRTY_CONTENT);
    }
}

bool HSVWheel::hsvFromPosition(double* hsv, int x, int y, int cx, int cy, int radius)
{
    double radiusd = (double)radius;
    double dist = sqrt(pow(cx - x, 2) + pow(cy - y, 2));

    if (dist <= radiusd)
    {
        double angle = atan2((double)(cy - y), (double)(x - cx));

        double distr = dist / radiusd;

        hsv[0] = angle / (2 * M_PI);
        hsv[1] = distr;
        hsv[2] = 1.0;

        return true;
    }
    else
    {
        return false;
    }
}

