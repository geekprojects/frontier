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
#include <frontier/widgets/scroller.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Scroller::Scroller(FrontierApp* ui) : Widget(ui, L"Scroller")
{
    initScroller(NULL);
}

Scroller::Scroller(FrontierApp* ui, Widget* child) : Widget(ui, L"Scroller")
{
    initScroller(child);
}

Scroller::Scroller(FrontierWindow* window) : Widget(window, L"Scroller")
{
    initScroller(NULL);
}

Scroller::Scroller(FrontierWindow* window, Widget* child) : Widget(window, L"Scroller")
{
    initScroller(child);
}

Scroller::~Scroller()
{
    if (m_scrollBar != NULL)
    {
        m_scrollBar->decRefCount();
    }
    if (m_child != NULL)
    {
        m_child->decRefCount();
    }
    if (m_childSurface != NULL)
    {
        delete m_childSurface;
    }
}

void Scroller::initScroller(Widget* child)
{
    m_childSurface = NULL;

    m_scrollBar = new ScrollBar(m_app);
    m_scrollBar->incRefCount();
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

    m_minSize.width = 50;
    m_minSize.height = 50;
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    if (m_child != NULL)
    {
        m_child->calculateSize();

        Size childMax = m_child->getMaxSize();
        m_minSize.setMin(childMax);
    }
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
    m_app->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        STATE_NONE,
        0, 0,
        m_setSize.width - (m_scrollBar->getWidth() + 1), m_setSize.height);

    if (m_child != NULL)
    {
        Size childSize = m_child->getSize();
#ifdef DEBUG_UI_SCROLLER
        log(DEBUG, "draw: scroller width=%d, height=%d", m_setSize.width, m_setSize.height);
        log(DEBUG, "draw: child width=%d, height=%d", m_child->getWidth(), m_child->getHeight());
#endif

        checkSurfaceSize(surface->isHighDPI());
        int childY = m_scrollBar->getPos();


        Size size = m_setSize;
        size.width -= 2;
        size.height -= 2;

        m_childSurface->clear(0);
        m_child->draw(m_childSurface, Rect(0, childY, m_child->getWidth(), size.height));

        size.setMin(childSize);
        if (surface->isHighDPI())
        {
            childY *= 2;
            size.width *= 2;
            size.height *= 2;
        }

        surface->blit(1, 1, m_childSurface, 0, childY, size.width, size.height);
    }

    // TODO: Make this only show if necessary
    SurfaceViewPort scrollbarVP(surface, m_scrollBar->getX(), m_scrollBar->getY(), m_scrollBar->getWidth(), m_scrollBar->getHeight());
    ((Widget*)m_scrollBar)->draw(&scrollbarVP, Rect(0, 0, m_scrollBar->getWidth(), m_scrollBar->getHeight()));

    return true;
}

Widget* Scroller::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseEvent* mouseEvent = (MouseEvent*)event;
#if 0
            Vector2D thisPos = Widget::getAbsolutePosition();
            log(DEBUG, "handleMessage: Mouse: pos=%d,%d, absPos=%d,%d, scrollPos=%d", imsg->event.button.x, imsg->event.button.y, thisPos.x, thisPos.y, m_scrollBar->getPos());
#endif

            int x = mouseEvent->x;
            int y = mouseEvent->y;

            if (m_scrollBar->intersects(x, y))
            {
                return m_scrollBar->handleEvent(event);
            }
            else
            {
                switch (event->eventType)
                {
                    case FRONTIER_EVENT_MOUSE_BUTTON:
                    {
                        MouseButtonEvent mouseButtonEvent = *((MouseButtonEvent*)event);
                        mouseButtonEvent.y += m_scrollBar->getPos();
                        return m_child->handleEvent(&mouseButtonEvent);
                    }


                    case FRONTIER_EVENT_MOUSE_MOTION:
                    {
                        MouseMotionEvent mouseMotionEvent = *((MouseMotionEvent*)event);
                        mouseMotionEvent.y += m_scrollBar->getPos();
                        return m_child->handleEvent(&mouseMotionEvent);
                    }

                    default:
                        break;
                }
            }
        } break;

        case FRONTIER_EVENT_MOUSE_SCROLL:
            return m_scrollBar->handleEvent(event);

        default:
            break;
    }

    return this;
}

void Scroller::setChild(Widget* child)
{
    m_child = child;
    m_child->incRefCount();
    m_child->setParent(this);
}

void Scroller::dump(int level)
{
    Widget::dump(level);

    if (m_child != NULL)
    {
        m_child->dump(level + 1);
    }

    m_scrollBar->dump(level + 1);
}

