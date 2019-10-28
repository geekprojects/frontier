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
    drawBorder(surface);

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
            setWidgetClass(L"root");
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
                    // TODO: Fancier CSS rules!
                    setWidgetClass(L"nested");
                }
            }
        }
    }

/*Size borderSize =*/ getBorderSize();

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);

    Size borderSize = getBorderSize();

int paddingTop = getStyle("padding-top");
//int paddingRight = getStyle("padding-right");
//int paddingBottom = getStyle("padding-bottom");
int paddingLeft = getStyle("padding-left");

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
                m_minSize.width += paddingLeft;
            }
            if (m_maxSize.width > 0)
            {
                m_maxSize.width += paddingLeft;
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
                m_minSize.height += paddingTop;
            }
            if (m_maxSize.height > 0)
            {
                m_maxSize.height += paddingTop;
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

    m_minSize.width += borderSize.width;
    m_minSize.height += borderSize.height;
    m_maxSize.width += borderSize.width;
    m_maxSize.height += borderSize.height;

    if (getStyle("expand-horizontal") == 1)
    {
        m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    }
    if (getStyle("expand-horizontal") == 1)
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

Size borderSize = getBorderSize();
int paddingTop = getStyle("padding-top");
//int paddingRight = getStyle("padding-right");
//int paddingBottom = getStyle("padding-bottom");
//int paddingLeft = getStyle("padding-left");

    if (m_horizontal)
    {
        major = m_setSize.width;
        minor = m_setSize.height;

    major -= borderSize.width;
    minor -= borderSize.height;
    }
    else
    {
        major = m_setSize.height;
        minor = m_setSize.width;
    major -= borderSize.height;
    minor -= borderSize.width;
    }

    major -= (m_children.size() - 1) * paddingTop;

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

    int majorPos = 0;
    int minorPos = 0;

if (m_horizontal)
{
majorPos = getStyle("margin-left");
minorPos = getStyle("margin-top");
}
else
{
majorPos = getStyle("margin-top");
minorPos = getStyle("margin-left");
}

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

        majorPos += childMajor + paddingTop;

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

