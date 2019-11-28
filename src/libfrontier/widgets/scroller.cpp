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
    if (m_childSurface != NULL)
    {
        delete m_childSurface;
    }
}

void Scroller::initScroller(Widget* child)
{
    m_childSurface = NULL;

    m_vScrollBar = new ScrollBar(m_app, false);
    m_vScrollBar->incRefCount();
    m_vScrollBar->setParent(this);
    m_children.push_back(m_vScrollBar);

    m_hScrollBar = new ScrollBar(m_app, true);
    m_hScrollBar->incRefCount();
    m_hScrollBar->setParent(this);
    m_children.push_back(m_hScrollBar);

    m_child = child;
    if (child != NULL)
    {
        setChild(child);
    }
}

void Scroller::calculateSize()
{
    m_vScrollBar->calculateSize();
    m_hScrollBar->calculateSize();

    m_minSize.width = 50;
    m_minSize.height = 50;
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    if (m_child != NULL)
    {
        m_child->calculateSize();

        Size childMax = m_child->getMaxSize();
        m_minSize.setMin(childMax);
    }

    m_minSize.width += m_vScrollBar->getMinSize().width;
    m_minSize.height += m_hScrollBar->getMinSize().height;
}

void Scroller::layout()
{
    BoxModel boxModel = getBoxModel();

    Size childMin = m_child->getMinSize();
    Size childMax = m_child->getMaxSize();

    m_drawSize.width = m_setSize.width - (boxModel.getWidth() + m_vScrollBar->getMinSize().width);
    m_drawSize.height = m_setSize.height - (boxModel.getHeight() + m_hScrollBar->getMinSize().height);

    Size childSize = m_drawSize;
    childSize.setMin(childMax);
    childSize.setMax(childMin);

    m_child->setPosition(0, 0);
    m_child->setSize(childSize);
    m_child->layout();

    m_vScrollBar->setPosition(m_setSize.width - m_hScrollBar->getMinSize().width, 0);
    m_vScrollBar->setSize(Size(m_vScrollBar->getMinSize().width, m_drawSize.height));
    m_vScrollBar->set(0, childSize.height, m_drawSize.height);

    m_hScrollBar->setPosition(0, m_setSize.height - m_vScrollBar->getMinSize().height);
    m_hScrollBar->setSize(Size(m_drawSize.width, m_hScrollBar->getMinSize().height));
    m_hScrollBar->set(0, childSize.width, m_drawSize.width);

    m_drawSize.setMin(childSize);
}

void Scroller::checkSurfaceSize(bool highDPI)
{
    int w = m_child->getWidth();
    int h = m_child->getHeight();
    if (highDPI)
    {
        w *= 2;
        h *= 2;
    }

    if (m_childSurface == NULL ||
        w != (int)m_childSurface->getWidth() ||
        h != (int)m_childSurface->getHeight())
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

    SurfaceViewPort mainVP(
        surface,
        0,
        0,
        surface->getWidth() - (m_vScrollBar->getWidth() + 1),
        surface->getHeight() - (m_hScrollBar->getHeight() + 1));
    drawBorder(&mainVP);

    if (m_child != NULL)
    {
#ifdef DEBUG_UI_SCROLLER
        log(DEBUG, "draw: scroller width=%d, height=%d", m_setSize.width, m_setSize.height);
        log(DEBUG, "draw: child width=%d, height=%d", m_child->getWidth(), m_child->getHeight());
#endif

        checkSurfaceSize(surface->isHighDPI());
        int childY = m_vScrollBar->getPos();
        int childX = m_hScrollBar->getPos();

        m_childSurface->clear(0);
        m_child->draw(m_childSurface, Rect(childX, childY, m_child->getWidth(), m_drawSize.height));

        Size scaledDrawSize = m_drawSize;
        if (surface->isHighDPI())
        {
            childX *= 2;
            childY *= 2;
            scaledDrawSize.width *= 2;
            scaledDrawSize.height *= 2;
        }

        BoxModel boxModel = getBoxModel();
        surface->blit(
            boxModel.getLeft(), boxModel.getTop(),
            m_childSurface,
            childX, childY,
            scaledDrawSize.width, scaledDrawSize.height);
    }

    // TODO: Make this only show if necessary
    SurfaceViewPort scrollbarVP(
        surface,
        m_vScrollBar->getX(), m_vScrollBar->getY(),
        m_vScrollBar->getWidth(), m_vScrollBar->getHeight());
    ((Widget*)m_vScrollBar)->draw(&scrollbarVP, Rect(0, 0, m_vScrollBar->getWidth(), m_vScrollBar->getHeight()));

    SurfaceViewPort scrollbarVPH(
        surface,
        m_hScrollBar->getX(), m_hScrollBar->getY(),
        m_hScrollBar->getWidth(), m_hScrollBar->getHeight());
    ((Widget*)m_hScrollBar)->draw(&scrollbarVPH, Rect(0, 0, m_hScrollBar->getWidth(), m_hScrollBar->getHeight()));

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
            log(DEBUG, "handleMessage: Mouse: pos=%d,%d, absPos=%d,%d, scrollPos=%d", imsg->event.button.x, imsg->event.button.y, thisPos.x, thisPos.y, m_vScrollBar->getPos());
#endif

            int x = mouseEvent->x;
            int y = mouseEvent->y;

            if (m_vScrollBar->intersects(x, y))
            {
                return m_vScrollBar->handleEvent(event);
            }
            else if (m_hScrollBar->intersects(x, y))
            {
                return m_hScrollBar->handleEvent(event);
            }
            else
            {
                switch (event->eventType)
                {
                    case FRONTIER_EVENT_MOUSE_BUTTON:
                    case FRONTIER_EVENT_MOUSE_MOTION:
                    {
                        mouseEvent->x += m_hScrollBar->getPos();
                        mouseEvent->y += m_vScrollBar->getPos();
                        return m_child->handleEvent(mouseEvent);
                    }

                    default:
                        break;
                }
            }
        } break;

        case FRONTIER_EVENT_MOUSE_SCROLL:
            m_vScrollBar->handleEvent(event);
            m_hScrollBar->handleEvent(event);
            return this;

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

    m_children.clear();
    m_children.push_back(child);
    m_children.push_back(m_vScrollBar);
}

void Scroller::dump(int level)
{
    Widget::dump(level);

    if (m_child != NULL)
    {
        m_child->dump(level + 1);
    }

    m_vScrollBar->dump(level + 1);
}

