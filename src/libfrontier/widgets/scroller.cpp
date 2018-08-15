
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek;
using namespace Geek::Gfx;

Scroller::Scroller(FrontierApp* ui) : Widget(ui)
{
    m_preferredHeight = 200;
    m_child = NULL;
    m_childSurface = NULL;

    m_scrollBar = new ScrollBar(ui);
    m_scrollBar->setParent(this);
}

Scroller::Scroller(FrontierApp* ui, Widget* child) : Widget(ui)
{
    m_preferredHeight = 200;
    m_childSurface = NULL;

    m_scrollBar = new ScrollBar(ui);

    setChild(child);
    m_scrollBar->setParent(this);
}

Scroller::~Scroller()
{
}

void Scroller::calculateSize()
{
    m_width = 100;
    m_height = m_preferredHeight;
    m_dirty = false;

    m_scrollBar->calculateSize();
    m_scrollBar->setWidth(20);

    if (m_child != NULL)
    {
        m_child->setPosition(0, 0);
        m_child->calculateSize();

        m_width = m_child->getWidth() + m_scrollBar->getWidth() + 2;

        m_scrollBar->set(0, m_child->getHeight(), m_height - 2);
    }

}

void Scroller::setWidth(int width)
{
    m_width = width;
    if (m_child != NULL)
    {
        if (m_child->getWidth()  < m_width - getWidthOverhead())
        {
            m_child->setWidth(m_width - getWidthOverhead());
        }
    }
}

void Scroller::checkSurfaceSize()
{
    if (m_childSurface == NULL ||
        m_child->getWidth() != m_childSurface->getWidth() ||
        m_child->getHeight() != m_childSurface->getHeight())
    {
        if (m_childSurface != NULL)
        {
            delete m_childSurface;
        }
        m_childSurface = new Surface(m_child->getWidth(), m_child->getHeight(), 4);
    }
}

bool Scroller::draw(Surface* surface)
{
    surface->drawRect(0, 0, m_width - (m_scrollBar->getWidth() - 2), m_height, 0xffffffff);

    if (m_child != NULL)
    {
        int cw = m_width - (m_scrollBar->getWidth() + 2);
        int ch = m_height - 2;
        if (cw > m_child->getWidth())
        {
            cw = m_child->getWidth();
        }
        if (ch > m_child->getHeight())
        {
            ch = m_child->getHeight();
        }

#ifdef DEBUG_UI_SCROLLER
        printf("Scroller::draw: scroller width=%d, height=%d\n", m_width, m_height);
        printf("Scroller::draw: child width=%d, height=%d\n", m_child->getWidth(), m_child->getHeight());
        printf("Scroller::draw: cw=%d, ch=%d\n", cw, ch);
#endif

        checkSurfaceSize();

        m_childSurface->clear(0);
        m_child->draw(m_childSurface);
        surface->blit(1, 1, m_childSurface, 0, m_scrollBar->getPos(), cw, ch);
    }

    m_scrollBar->setPosition(m_width - m_scrollBar->getWidth(), 0);
    m_scrollBar->setHeight(m_height);
    SurfaceViewPort scrollbarVP(surface, m_width - m_scrollBar->getWidth(), 0, m_scrollBar->getWidth(), m_height);
    m_scrollBar->draw(&scrollbarVP);

    return true;
}

Widget* Scroller::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
        {
            int x = imsg->event.button.x;
            int y = imsg->event.button.y;
            if (m_scrollBar->intersects(x, y))
            {
                return m_scrollBar->handleMessage(msg);
            }
            else
            {
                imsg->event.button.y += m_scrollBar->getPos();
                return m_child->handleMessage(imsg);
            }
        }
    }
    return this;
}

void Scroller::setChild(Widget* child)
{
    m_child = child;
    m_child->setParent(this);
}

