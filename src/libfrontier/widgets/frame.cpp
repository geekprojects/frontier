
#include <frontier/frontier.h>
#include <frontier/widgets.h>

#undef DEBUG_UI_FRAME

using namespace std;
using namespace Geek;
using namespace Geek::Gfx;

Frame::Frame(FrontierApp* ui, bool horizontal) : Widget(ui)
{
    m_horizontal = horizontal;
    m_border = false;
}

Frame::~Frame()
{
}

void Frame::add(Widget* widget)
{
    m_children.push_back(widget);
    widget->setParent(this);
    widget->setDirty();
}

bool Frame::draw(Surface* surface)
{
    if (m_border)
    {
        surface->drawRect(0, 0, m_width, m_height, 0xffffffff);
    }

    int x = m_margin;
    int y = m_margin;
    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        SurfaceViewPort viewport(surface, x, y, child->getWidth(), child->getHeight());
        child->setPosition(x, y);
        child->draw(&viewport);
        if (m_horizontal)
        {
            x += child->getWidth();
            x += m_padding;
        }
        else
        {
            y += child->getHeight();
            y += m_padding;
        }
    }
    return true;
}

void Frame::calculateSize()
{
#ifdef DEBUG_UI_FRAME
    printf("Frame::calculateSize: %p: Calculating...\n", this);
#endif
    m_width = 0;
    m_height = 0;
    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* w = *it;
#ifdef DEBUG_UI_FRAME
        printf("Frame::calculateSize: %p: calculating child: %p...\n", this, *it);
#endif
        w->calculateSize();
    }

    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        int childWidth = (*it)->getWidth();
        int childHeight = (*it)->getHeight();
#ifdef DEBUG_UI_FRAME
        printf("Frame::calculateSize: %p: sizing child: %p: width=%d, height=%d\n", this, (*it), childWidth, childHeight);
#endif

        if (m_horizontal)
        {
            if (childHeight > m_height)
            {
                m_height = childHeight;
            }
            if (m_width > 0)
            {
                m_width += m_padding;
            }
            m_width += childWidth;
        }
        else
        {
            if (childWidth > m_width)
            {
                m_width = childWidth;
            }
            if (m_height > 0)
            {
                m_height += m_padding;
            }
            m_height += childHeight;
        }
    }

    for (it = m_children.begin(); it != m_children.end(); it++)
    {

        if (m_horizontal)
        {
            (*it)->setHeight(m_height);
        }
        else
        {
            (*it)->setWidth(m_width);
        }
    }

    m_width += 2 * m_margin;
    m_height += 2 * m_margin;

    m_dirty = false;
#ifdef DEBUG_UI_FRAME
    printf("Frame::calculateSize: %p: Done\n", this);
#endif
}

void Frame::setWidth(int width)
{
    if (width < m_width)
    {
        printf("Frame::setWidth: %p: OH NOES! WIDTH IS TOO SMALL\n", this);
    }
    int extra = width - m_width;

    m_width = width;

    if (extra <= 0 || m_children.size() == 0)
    {
        return;
    }

    if (m_horizontal)
    {
        // Spread the extra out over our children
        extra /= m_children.size();
    }

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        child->setWidth(child->getWidth() + extra);
    }
}

void Frame::setHeight(int height)
{
    if (height < m_height)
    {
        printf("Frame::setHeight: %p: OH NOES! HEIGHT IS TOO SMALL\n", this);
    }
    int extra = height - m_height;

    m_height = height;

    if (extra <= 0 || m_children.size() == 0)
    {
        return;
    }

    if (!m_horizontal)
    {
        // Spread the extra out over our children
        extra /= m_children.size();
    }

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        child->setHeight(child->getHeight() + extra);
    }
}

Widget* Frame::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
        {
            int x = imsg->event.button.x;
            int y = imsg->event.button.y;
            Vector2D thisPos = getAbsolutePosition();
            vector<Widget*>::iterator it;
            for (it = m_children.begin(); it != m_children.end(); it++)
            {
                Widget* child = *it;
                if (child->intersects(x, y))
                {
                    return child->handleMessage(msg);
                }
            }
        }
    }

    return NULL;
}

