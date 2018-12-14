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

Frame::Frame(FrontierApp* ui, bool horizontal) : Widget(ui)
{
    m_horizontal = horizontal;
    m_border = false;
}

Frame::Frame(FrontierWindow* window, bool horizontal) : Widget(window)
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
    printf("Frame::calculateSize: %p: Calculating...\n", this);
#endif

    if (m_parent == NULL)
    {
        m_margin = 0;
    }
    else
    {
        // Parent is a frame
        Frame* parentFrame = dynamic_cast<Frame*>(m_parent);
        if (parentFrame != NULL)
        {
#ifdef DEBUG_UI_FRAME
            printf("Frame::calculateSize: %p: Parent is Frame, margin=%d\n", this, parentFrame->getMargin());
            //if (parentFrame->getMargin() > 0)
#endif
            {
                m_margin = 0;
            }
        }
    }

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        Widget* child = *it;
        child->calculateSize();

        Size childMin = child->getMinSize();
        Size childMax = child->getMaxSize();

#ifdef DEBUG_UI_FRAME
        printf("Frame::calculateSize: %p: sizing child: %p: min=%s, max=%s\n", this, (*it), childMin.toString().c_str(), childMax.toString().c_str());
#endif

        if (m_horizontal)
        {
            m_minSize.setMaxHeight(childMin);
            m_maxSize.setMaxHeight(childMax);

            if (m_minSize.width > 0)
            {
                m_minSize.width += m_padding;
            }
            if (m_maxSize.width > 0)
            {
                m_maxSize.width += m_padding;
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
                m_minSize.height += m_padding;
            }
            if (m_maxSize.height > 0)
            {
                m_maxSize.height += m_padding;
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

    m_minSize.width += 2 * m_margin;
    m_minSize.height += 2 * m_margin;
    m_maxSize.width += 2 * m_margin;
    m_maxSize.height += 2 * m_margin;

#ifdef DEBUG_UI_FRAME
    printf("Frame::calculateSize: %p: Done: min=%s, max=%s\n", this, m_minSize.toString().c_str(), m_maxSize.toString().c_str());
#endif
}

/*
 * This assumes that the calculateSize has been called and min/maxes have been set and that a size has been set
 */
void Frame::layout()
{
    int major;
    int minor;

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

    major -= (2 * m_margin);
    minor -= 2 * m_margin;
    if (!m_children.empty())
    {
        major -= (m_children.size() - 1) * m_padding;
    }

#if 0
    printf("Frame::layout: major=%d, minor=%d\n", major, minor);
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


/*
        if (childMajorMax < q)
        {
            slack -= q - childMajorMax;
printf("Frame::layout: Max < q: slack=%d\n", (q - childMajorMax));
        }
        else if (childMajorMin > q)
        {
            slack -= q - childMajorMin;
printf("Frame::layout: Min < q: slack=%d\n", (q - childMajorMax));
        }
else
{
slackable++;
}
*/

/*
        if (childMajorMin > q)
        {
            slack -= childMajorMin - q;
            //slackable++;
        }
*/
    }

    int slack = major - min;
#ifdef DEBUG_UI_FRAME
    printf("Frame::layout: major=%d, slack=%d, slackable=%d\n", major, slack, slackable);
#endif

    int i;

    int majorPos = m_margin;
    int minorPos = m_margin;

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
        printf("Frame::layout: Child: min=%d, max=%d, settingTo=%d\n", childMajorMin, childMajorMax, childMajor);
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

        majorPos += childMajor + m_padding;

        child->layout();
    }
}

#if 0
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
#endif

Widget* Frame::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION ||
            imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_WHEEL)
        {
            int x = imsg->event.button.x;
            int y = imsg->event.button.y;

            vector<Widget*>::iterator it;
            for (it = m_children.begin(); it != m_children.end(); it++)
            {
                Widget* child = *it;
                if (child->intersects(x, y))
                {
                    return child->handleMessage(msg);
                }
            }
            if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
            {
                return this;
            }
        }
    }

    return NULL;
}

