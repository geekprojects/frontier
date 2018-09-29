/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Scroller::Scroller(FrontierApp* ui) : Widget(ui)
{
    initScroller(NULL);
}

Scroller::Scroller(FrontierApp* ui, Widget* child) : Widget(ui)
{
    initScroller(child);
}

Scroller::Scroller(FrontierWindow* window) : Widget(window)
{
    initScroller(NULL);
}

Scroller::Scroller(FrontierWindow* window, Widget* child) : Widget(window)
{
    initScroller(child);
}

Scroller::~Scroller()
{
}

void Scroller::initScroller(Widget* child)
{
    m_childSurface = NULL;

    m_scrollBar = new ScrollBar(m_ui);
    m_scrollBar->setParent(this);

    m_child = child;
    if (child != NULL)
    {
        setChild(child);
    }
}


void Scroller::calculateSize()
{
    m_scrollBar->calculateSize();

    if (m_child != NULL)
    {
        m_child->calculateSize();
    }

    //Size childMin = m_child->getMinSize();
    Size childMax = m_child->getMaxSize();
    //m_minSize.width = childMin.width + m_scrollBar->getMinSize().width;
    //m_minSize.height = childMin.height + 2;
    m_minSize.width = 50;
    m_minSize.height = 50;
    m_minSize.setMin(childMax);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
}

void Scroller::layout()
{
    m_child->setPosition(0, 0);

    Size childMin = m_child->getMinSize();
    Size childMax = m_child->getMaxSize();

    Size childSize;
    childSize.width = m_setSize.width - m_scrollBar->getMinSize().width;
    childSize.height = m_setSize.height;
    childSize.setMin(childMax);
    childSize.setMax(childMin);
    m_child->setSize(childSize);
    m_child->layout();

    m_scrollBar->setPosition(m_setSize.width - m_scrollBar->getMinSize().width, 0);
    m_scrollBar->setSize(Size(m_scrollBar->getMinSize().width, m_setSize.height));

    m_scrollBar->set(0, m_child->getHeight(), (m_setSize.height - 2));
}

/*
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
*/

void Scroller::checkSurfaceSize(bool highDPI)
{
    if (m_childSurface == NULL ||
        m_child->getWidth() != (int)m_childSurface->getWidth() ||
        m_child->getHeight() != (int)m_childSurface->getHeight())
    {
        if (m_childSurface != NULL)
        {
            delete m_childSurface;
        }
if (highDPI)
{
        m_childSurface = new HighDPISurface(m_child->getWidth(), m_child->getHeight(), 4);
}
else
{
        m_childSurface = new Surface(m_child->getWidth(), m_child->getHeight(), 4);
}
    }
}

bool Scroller::draw(Surface* surface)
{
    //surface->drawRect(0, 0, m_setSize.width - (m_scrollBar->getWidth() - 2), m_setSize.height, 0xffffffff);
    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        STATE_NONE,
        0, 0,
        m_setSize.width - (m_scrollBar->getWidth() + 1), m_setSize.height);

    if (m_child != NULL)
    {
/*
        int cw = m_setSize.width - (m_scrollBar->getWidth() + 2);
        int ch = m_setSize.height - 2;
        if (cw > m_child->getWidth())
        {
            cw = m_child->getWidth();
        }
        if (ch > m_child->getHeight())
        {
            ch = m_child->getHeight();
        }
*/

Size childSize = m_child->getSize();
#ifdef DEBUG_UI_SCROLLER
        printf("Scroller::draw: scroller width=%d, height=%d\n", m_width, m_height);
        printf("Scroller::draw: child width=%d, height=%d\n", m_child->getWidth(), m_child->getHeight());
        printf("Scroller::draw: cw=%d, ch=%d\n", cw, ch);
#endif

        checkSurfaceSize(surface->isHighDPI());

        if (surface->isHighDPI())
        {
            childSize.width *= 2;
            childSize.height *= 2;
        }

        m_childSurface->clear(0);
        m_child->draw(m_childSurface);
        surface->blit(1, 1, m_childSurface, 0, m_scrollBar->getPos(), childSize.width, childSize.height);
    }

    // TODO: Make this only show if necessary
    SurfaceViewPort scrollbarVP(surface, m_scrollBar->getX(), m_scrollBar->getY(), m_scrollBar->getWidth(), m_scrollBar->getHeight());
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

            Vector2D thisPos = Widget::getAbsolutePosition();
printf("Scroller::handleMessage: Mouse: pos=%d,%d, absPos=%d,%d, scrollPos=%d\n", imsg->event.button.x, imsg->event.button.y, thisPos.x, thisPos.y, m_scrollBar->getPos());

            int x = imsg->event.button.x;
            int y = imsg->event.button.y;

            if (m_scrollBar->intersects(x, y))
            {
                return m_scrollBar->handleMessage(msg);
            }
            else
            {
                //imsg->event.button.y -= m_scrollBar->getPos();
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

