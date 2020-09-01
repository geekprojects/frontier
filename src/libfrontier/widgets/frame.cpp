/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
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

FRONTIER_WIDGET(Frame, Frontier::Frame)

Frame::Frame(FrontierApp* ui) : Widget(ui, L"Frame")
{
    setProperty(FRONTIER_PROP_HORIZONTAL, true);
    m_widgetNames.insert(L"Frame");
}

Frame::Frame(FrontierApp* ui, bool horizontal) : Widget(ui, L"Frame")
{
    setProperty(FRONTIER_PROP_HORIZONTAL, horizontal);
    m_widgetNames.insert(L"Frame");
}

Frame::Frame(FrontierApp* ui, wstring widgetName, bool horizontal) : Widget(ui, widgetName)
{
    setProperty(FRONTIER_PROP_HORIZONTAL, horizontal);
    m_widgetNames.insert(L"Frame");
}

Frame::Frame(FrontierWindow* window, bool horizontal) : Widget(window, L"Frame")
{
    setProperty(FRONTIER_PROP_HORIZONTAL, horizontal);
    m_widgetNames.insert(L"Frame");
}

Frame::Frame(FrontierWindow* window, wstring widgetName, bool horizontal) : Widget(window, widgetName)
{
    setProperty(FRONTIER_PROP_HORIZONTAL, horizontal);
    m_widgetNames.insert(L"Frame");
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
    for (it = m_children.begin(); it != m_children.end(); ++it)
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
    bool dirtySize = isDirty(DIRTY_SIZE);
    if (dirtySize)
    {
        drawBorder(surface);
    }

    for (Widget* child : m_children)
    {
        if (dirtySize || child->isDirty() || child->hasChildren())
        {
            SurfaceViewPort viewport(surface, child->getX(), child->getY(), child->getWidth(), child->getHeight());
            child->draw(&viewport, Rect(0, 0, child->getWidth(), child->getHeight()));
        }
    }
    return true;
}

void Frame::calculateSize()
{
#ifdef DEBUG_UI_FRAME
    log(DEBUG, "calculateSize: %p: Calculating...", this);
#endif

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);

    BoxModel boxModel = getBoxModel();
    for (Widget* child : m_children)
    {
        if (child->isDirty(DIRTY_SIZE) || child->isDirty(DIRTY_STYLE))
        {
            child->calculateSize();
        }

        Size childMin = child->getMinSize();
        Size childMax = child->getMaxSize();

#ifdef DEBUG_UI_FRAME
        log(DEBUG, "calculateSize: %p: sizing child: %p: min=%s, max=%s", this, (*it), childMin.toString().c_str(), childMax.toString().c_str());
#endif

        if (getProperty(FRONTIER_PROP_HORIZONTAL).asBool())
        {
            m_minSize.setMaxHeight(childMin);
            m_maxSize.setMaxHeight(childMax);

            if (m_minSize.width > 0)
            {
                m_minSize.width += boxModel.paddingLeft;
            }
            if (m_maxSize.width > 0)
            {
                m_maxSize.width += boxModel.paddingLeft;
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
                m_minSize.height += boxModel.paddingTop;
            }
            if (m_maxSize.height > 0)
            {
                m_maxSize.height += boxModel.paddingTop;
            }
            m_minSize.height += childMin.height;
            m_maxSize.height += childMax.height;
        }
    }

    m_minSize.width += boxModel.getWidth();
    m_minSize.height += boxModel.getHeight();
    m_maxSize.width += boxModel.getWidth();
    m_maxSize.height += boxModel.getHeight();

    if (getStyle("expand-horizontal").asBool())
    {
        m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    }
    if (getStyle("expand-vertical").asBool())
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
    int majorWidgetSize;
    int minorWidgetSize;

    BoxModel boxModel = getBoxModel();

    bool horizontal = getProperty(FRONTIER_PROP_HORIZONTAL).asBool();

    if (horizontal)
    {
        majorWidgetSize = m_setSize.width;
        minorWidgetSize = m_setSize.height;

        major = majorWidgetSize - boxModel.getWidth();
        minor = minorWidgetSize - boxModel.getHeight();
    }
    else
    {
        majorWidgetSize = m_setSize.height;
        minorWidgetSize = m_setSize.width;
        major = majorWidgetSize - boxModel.getHeight();
        minor = minorWidgetSize - boxModel.getWidth();
    }

    major -= (m_children.size() - 1) * boxModel.paddingTop;

#if 0
    log(DEBUG, "layout: major=%d, minor=%d", major, minor);
#endif

    int q = major / m_children.size();
    int slackable = 0;

    int min = 0;

    for (Widget* child : m_children)
    {
        Size childMinSize = child->getMinSize();
        Size childMaxSize = child->getMaxSize();

        int childMajorMin = childMinSize.get(horizontal);
        int childMajorMax = childMaxSize.get(horizontal);

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

    int majorTotal = 0;
    vector<Widget*>::iterator it;
    for (it = m_children.begin(), i = 0; it != m_children.end(); ++it, i++)
    {
        Widget* child = *it;

        Size childMinSize = child->getMinSize();
        Size childMaxSize = child->getMaxSize();

        int childMajorMin = childMinSize.get(horizontal);
        int childMajorMax = childMaxSize.get(horizontal);

        int childMinorMin = childMinSize.get(!horizontal);
        int childMinorMax = childMaxSize.get(!horizontal);

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
        if (horizontal)
        {
            size = Size(childMajor, childMinor);
        }
        else
        {
            size = Size(childMinor, childMajor);
        }
        child->setSize(size);

        majorTotal += childMajor;
        if (i > 0)
        {
            majorTotal += boxModel.paddingTop;
        }
    }

    int majorPos = 0;
    int minorPos = 0;

    int horizontalAlign = FRONTIER_HORIZONTAL_ALIGN_LEFT;
    if (hasStyle("align-horizontal"))
    {
        horizontalAlign = getStyle("align-horizontal").asInt();
    }
    int verticalAlign = FRONTIER_VERTICAL_ALIGN_TOP;
    if (hasStyle("align-vertical"))
    {
        verticalAlign = getStyle("align-vertical").asInt();
    }
    int majorAlign;
    int minorAlign;
    if (horizontal)
    {
        majorPos = boxModel.marginLeft;
        minorPos = boxModel.marginTop;
        majorAlign = horizontalAlign;
        minorAlign = verticalAlign;
    }
    else
    {
        majorPos = boxModel.marginTop;
        minorPos = boxModel.marginLeft;
        majorAlign = verticalAlign;
        minorAlign = horizontalAlign;
    }

    if (majorAlign == FRONTIER_HORIZONTAL_ALIGN_CENTRE)
    {
        majorPos = (majorWidgetSize / 2) - (majorTotal / 2);
    }

    for (it = m_children.begin(), i = 0; it != m_children.end(); ++it, i++)
    {
        Widget* child = *it;
        Size size = child->getSize();
        int childMajor;
        if (horizontal)
        {
            int childMinorPos = minorPos;
            if (minorAlign == FRONTIER_HORIZONTAL_ALIGN_CENTRE)
            {
                childMinorPos = (minorWidgetSize / 2) - (size.height / 2);
            }
            child->setPosition(majorPos, childMinorPos);
            childMajor = size.width;
        }
        else
        {
            int childMinorPos = minorPos;
            if (minorAlign == FRONTIER_VERTICAL_ALIGN_MIDDLE)
            {
                childMinorPos = (minorWidgetSize / 2) - (size.width / 2);
            }
            child->setPosition(childMinorPos, majorPos);
            childMajor = size.height;
        }

        majorPos += childMajor + boxModel.paddingTop;

        if (isDirty(DIRTY_SIZE))
        {
            child->setDirty(DIRTY_CONTENT | DIRTY_SIZE, true);
        }

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

        for (Widget* child : m_children)
        {
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

void Frame::activateNext(Widget* activeChild)
{
log(DEBUG, "activateNext: %p: activeChild=%p", this, activeChild);
    if (m_children.empty())
    {
log(DEBUG, "activateNext: %p: No children. Stop", this);
/*
        if (m_parent != NULL && activeChild == NULL)
        {
            m_parent->activateNext(this);
        }
*/
        return;
    }

    if (activeChild == NULL)
    {
log(DEBUG, "activateNext: %p: From parent, try first child...", this);
        m_children.at(0)->activateNext(NULL);
        return;
    }
    else
    {
log(DEBUG, "activateNext: %p: From child, try next child", this);
        bool foundCurrent = false;
        for (Widget* child : m_children)
        {
            if (child == activeChild)
            {
log(DEBUG, "activateNext: %p:  -> found current!", this);
                foundCurrent = true;
            }
            else if (foundCurrent)
            {
                log(DEBUG, "activateNext: %p:  -> Next=%p", this, child);
                child->activateNext(NULL);
                return;
            }
        }

        log(DEBUG, "activateNext: %p: No next child, try parent...", this);
        if (m_parent != NULL)
        {
            m_parent->activateNext(this);
        }
    }
}

