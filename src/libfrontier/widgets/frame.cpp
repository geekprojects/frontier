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
#include <frontier/widgets/frame.h>

#include <stdio.h>

#undef DEBUG_UI_FRAME

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Frame::Frame(FrontierApp* ui, bool horizontal) : Widget(ui, L"Frame")
{
    m_horizontal = horizontal;
    m_border = false;
}

Frame::Frame(FrontierApp* ui, wstring widgetName, bool horizontal) : Widget(ui, widgetName)
{
    m_horizontal = horizontal;
    m_border = false;
}

Frame::Frame(FrontierWindow* window, bool horizontal) : Widget(window, L"Frame")
{
    m_horizontal = horizontal;
    m_border = false;
}

Frame::Frame(FrontierWindow* window, wstring widgetName, bool horizontal) : Widget(window, widgetName)
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
    widget->incRefCount();
    widget->setParent(this);
    widget->setDirty();
}

void Frame::remove(Widget* widget)
{
    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        if (child == widget)
        {
            m_children.erase(it);
            child->incRefCount();
            child->setParent(NULL);
            setDirty();

            break;
        }
    }
}

bool Frame::draw(Surface* surface)
{
    if (m_border)
    {
        surface->drawRect(0, 0, m_setSize.width, m_setSize.height, 0xff888888);
    }

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        SurfaceViewPort viewport(surface, child->getX(), child->getY(), child->getWidth(), child->getHeight());
        child->draw(&viewport, Rect(0, 0, child->getWidth(), child->getHeight()));

#if 0
        viewport.drawRect(0, 0, child->getWidth(), child->getHeight(), 0x00ff00);
#endif
    }
    return true;
}

void Frame::calculateSize()
{
#ifdef DEBUG_UI_FRAME
    log(DEBUG, "calculateSize: %p: Calculating...", this);
#endif

    if (!m_border)
    {
        if (m_parent == NULL)
        {
            setStyle(STYLE_MARGIN, 0);
        }
        else
        {
            // Parent is a frame
            Frame* parentFrame = dynamic_cast<Frame*>(m_parent);
            if (parentFrame != NULL)
            {
#ifdef DEBUG_UI_FRAME
                log(DEBUG, "calculateSize: %p: Parent is Frame, margin=%d", this, parentFrame->getMargin());
                //if (parentFrame->getMargin() > 0)
#endif
                {
                    setStyle(STYLE_MARGIN, 0);
                }
            }
        }
    }

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);

    int margin = (int)getStyle(STYLE_MARGIN);
    int padding = (int)getStyle(STYLE_PADDING);

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        child->calculateSize();

        Size childMin = child->getMinSize();
        Size childMax = child->getMaxSize();

#ifdef DEBUG_UI_FRAME
        log(DEBUG, "calculateSize: %p: sizing child: %p: min=%s, max=%s", this, (*it), childMin.toString().c_str(), childMax.toString().c_str());
#endif

        if (m_horizontal)
        {
            m_minSize.setMaxHeight(childMin);
            m_maxSize.setMaxHeight(childMax);

            if (m_minSize.width > 0)
            {
                m_minSize.width += padding;
            }
            if (m_maxSize.width > 0)
            {
                m_maxSize.width += padding;
            }
            m_minSize.width += childMin.width;
            m_maxSize.width += childMax.width;
        }
        else
        {
            m_minSize.setMaxWidth(childMin);
            m_maxSize.setMaxWidth(childMax);

            if (m_minSize.height > 0)
            {
                m_minSize.height += padding;
            }
            if (m_maxSize.height > 0)
            {
                m_maxSize.height += padding;
            }
            m_minSize.height += childMin.height;
            m_maxSize.height += childMax.height;
        }
    }

/*
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
*/

    m_minSize.width += 2 * margin;
    m_minSize.height += 2 * margin;
    m_maxSize.width += 2 * margin;
    m_maxSize.height += 2 * margin;

    if (hasStyle(STYLE_EXPAND_HORIZONTAL) && getStyle(STYLE_EXPAND_HORIZONTAL) == 1)
    {
        m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    }
    if (hasStyle(STYLE_EXPAND_VERTICAL) && getStyle(STYLE_EXPAND_VERTICAL) == 1)
    {
        m_maxSize.height = WIDGET_SIZE_UNLIMITED;
    }

#ifdef DEBUG_UI_FRAME
    log(DEBUG, "calculateSize: %p: Done: min=%s, max=%s", this, m_minSize.toString().c_str(), m_maxSize.toString().c_str());
#endif
}

/*
 * This assumes that the calculateSize has been called and min/maxes have been set and that a size has been set
 */
void Frame::layout()
{
    if (m_children.empty())
    {
        // Nothing to lay out!
        return;
    }

    int major;
    int minor;

    int margin = (int)getStyle(STYLE_MARGIN);
    int padding = (int)getStyle(STYLE_PADDING);

    if (m_horizontal)
    {
        major = m_setSize.width;
        minor = m_setSize.height;
    }
    else
    {
        major = m_setSize.height;
        minor = m_setSize.width;
    }

    major -= (2 * margin);
    minor -= 2 * margin;
    major -= (m_children.size() - 1) * padding;

#if 0
    log(DEBUG, "layout: major=%d, minor=%d", major, minor);
#endif

    int q = major / m_children.size();
    int slackable = 0;

    int min = 0;

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        Size childMinSize = child->getMinSize();
        Size childMaxSize = child->getMaxSize();

        int childMajorMin = childMinSize.get(m_horizontal);
        int childMajorMax = childMaxSize.get(m_horizontal);

        min += childMajorMin;
        if (childMajorMax > q)
        {
            slackable++;
        }
    }

    int slack = major - min;
#ifdef DEBUG_UI_FRAME
    log(DEBUG, "layout: major=%d, slack=%d, slackable=%d", major, slack, slackable);
#endif

    int i;

    int majorPos = margin;
    int minorPos = margin;

    for (it = m_children.begin(), i = 0; it != m_children.end(); it++, i++)
    {
        Widget* child = *it;


        Size childMinSize = child->getMinSize();
        Size childMaxSize = child->getMaxSize();

        int childMajorMin = childMinSize.get(m_horizontal);
        int childMajorMax = childMaxSize.get(m_horizontal);

        int childMinorMin = childMinSize.get(!m_horizontal);
        int childMinorMax = childMaxSize.get(!m_horizontal);

        int childMajor = childMajorMin;
        int childMinor = minor;

        if (childMajorMax < q)
        {
            childMajor = childMajorMax;
        }
        if (childMajorMin > q)
        {
            childMajor = childMajorMin;
        }

        if (childMajor < childMajorMax && slackable > 0)
        {
            int s = slack / slackable;
            slack -= s;
            slackable--;

            childMajor += s;

            if (childMajor > childMajorMax)
            {
                int d = (childMajor - childMajorMax);
                childMajor -= d;
                slack += d;
            }
        }

        if (childMinor > childMinorMax)
        {
            childMinor = childMinorMax;
        }
        if (childMinor < childMinorMin)
        {
            childMinor = childMinorMin;
        }

#ifdef DEBUG_UI_FRAME
        log(DEBUG, "layout: Child: min=%d, max=%d, settingTo=%d", childMajorMin, childMajorMax, childMajor);
#endif

        Size size;
        if (m_horizontal)
        {
            size = Size(childMajor, childMinor);
            child->setPosition(majorPos, minorPos);
        }
        else
        {
            size = Size(childMinor, childMajor);
            child->setPosition(minorPos, majorPos);
        }
        child->setSize(size);

        majorPos += childMajor + padding;

        child->layout();
    }
}

Widget* Frame::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        vector<Widget*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); it++)
        {
            Widget* child = *it;
            if (child->intersects(x, y))
            {
                return child->handleEvent(event);
            }
        }
        if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
        {
            return this;
        }
    }

    return NULL;
}

