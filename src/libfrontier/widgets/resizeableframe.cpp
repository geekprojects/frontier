/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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
#include <frontier/widgets/resizeableframe.h>

#include <stdio.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#undef DEBUG_RESIZEABLE_FRAME

ResizeableFrame::ResizeableFrame(FrontierApp* ui, bool horizontal) : Frame(ui, L"ResizeableFrame", horizontal)
{
    m_dragging = false;
    m_dragWidget = 0;
}

ResizeableFrame::ResizeableFrame(FrontierWindow* window, bool horizontal) : Frame(window, L"ResizeableFrame", horizontal)
{
    m_dragging = false;
    m_dragWidget = 0;
}

ResizeableFrame::~ResizeableFrame()
{
}

void ResizeableFrame::add(Widget* widget)
{
    addWithSize(widget, 0);
}

void ResizeableFrame::addWithSize(Widget* widget, int setPc)
{
    m_children.push_back(widget);

    widget->incRefCount();
    widget->setParent(this);
    widget->setDirty();

    if (setPc == 0)
    {
        m_sizes.clear();

        float pc = 100.0 / (float)m_children.size();

        unsigned int i;
        for (i = 0; i < m_children.size(); i++)
        {
            m_sizes.push_back(pc);
        }
    }
    else
    {
        m_sizes.push_back(setPc);
    }
}

void ResizeableFrame::layout()
{
    int major;
    int minor;
    int majorPos;
    int minorPos;
    int padding;

    BoxModel boxModel = getBoxModel();

    if (!isDirty(DIRTY_SIZE))
    {
        return;
    }

    if (m_horizontal)
    {
        major = m_setSize.width - boxModel.getWidth();
        minor = m_setSize.height - boxModel.getHeight();
        majorPos = boxModel.getLeft();
        minorPos = boxModel.getTop();
        padding = boxModel.paddingLeft;
    }
    else
    {
        major = m_setSize.height - boxModel.getHeight();
        minor = m_setSize.width - boxModel.getWidth();
        majorPos = boxModel.getTop();
        minorPos = boxModel.getLeft();
        padding = boxModel.paddingTop;
    }

    if (!m_children.empty())
    {
        major -= (m_children.size() - 1) * padding;
    }

    vector<Widget*>::iterator it;
    int i;

    // First, work out if we have any children that are too big or too small
    for (it = m_children.begin(), i = 0; it != m_children.end(); ++it, ++i)
    {
        Widget* child = *it;
        Size childMinSize = child->getMinSize();
        Size childMaxSize = child->getMaxSize();

        int childMajorMin = childMinSize.get(m_horizontal);
        int childMajorMax = childMaxSize.get(m_horizontal);

        float pc = m_sizes.at(i);
        int childMajor = (int)((float)major * (pc / 100.0));

#ifdef DEBUG_RESIZEABLE_FRAME
            log(Geek::DEBUG, "layout: pc=%0.2f, childMajor=%d, minSize=%d, maxSize=%d", pc, childMajor, childMajorMin, childMajorMax);
#endif

        if (childMajor < childMajorMin)
        {
            // Too small!
            int under = childMajorMin - childMajor;
            childMajor = childMajorMin;
            float extrapc = (((float)under / (float)major) * 100.0);
            //m_sizes[i] += extrapc;
#ifdef DEBUG_RESIZEABLE_FRAME
            log(Geek::DEBUG, "layout:  -> Under min by %d (%0.2f%%)", under, extrapc);
#endif

            // Borrow some space from a neighbour?
            float d;
            d = borrow(i - 1, -extrapc, major, -1);
            extrapc += d;
            m_sizes[i] -= d;
            if (d != extrapc)
            {
                d = borrow(i + 1, -extrapc, major, 1);
                extrapc += d;
                m_sizes[i] -= d;
            }
        }
        else if (childMajor > childMajorMax)
        {
            // Too big!
            int over = childMajor - childMajorMax;
            childMajor = childMajorMax;
            float extrapc = (((float)over / (float)major) * 100.0);

#ifdef DEBUG_RESIZEABLE_FRAME
            log(Geek::DEBUG, "layout:  -> Over max by %d (%0.2f%%), shrinking", over, extrapc);
#endif

            // Give some space from a neighbour?
            float d;
            d = borrow(i - 1, extrapc, major, -1);
            extrapc -= d;
            m_sizes[i] -= d;
            if (extrapc > 0)
            {
                d = borrow(i + 1, extrapc, major, 1);
                m_sizes[i] -= d;
            }
        }
    }

    // Actually set the child sizes and positions
    for (it = m_children.begin(), i = 0; it != m_children.end(); ++it, ++i)
    {
        Widget* child = *it;

        float pc = m_sizes.at(i);
        int childMajor = (int)((float)major * (pc / 100.0));
        int childMinor = minor;
/*
            int maxMinor = child->getMaxSize().get(!m_horizontal);
            if (childMinor > maxMinor)
            {
                childMinor = maxMinor;
            }
*/

#ifdef DEBUG_RESIZEABLE_FRAME
        log(DEBUG, "layout: majorPos=%d, m_sizes[%d]=%0.2f%%: major=%d", majorPos, i, pc, childMajor);
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

float ResizeableFrame::borrow(int which, float amount, int major, int direction)
{
    if (which < 0 || which >= (int)m_children.size())
    {
        return 0.0;
    }

    if (amount == 0)
    {
        return 0.0;
    }

#ifdef DEBUG_RESIZEABLE_FRAME
    log(DEBUG, "borrow: which=%d, amount=%0.2f%%\n", which, amount);
#endif

    Widget* child = m_children[which];
    Size childMinSize = child->getMinSize();
    Size childMaxSize = child->getMaxSize();

    int childMajorMin = childMinSize.get(m_horizontal);
    int childMajorMax = childMaxSize.get(m_horizontal);

    float pc = m_sizes.at(which);
    int childMajor = (int)((float)major * (pc / 100.0));

#ifdef DEBUG_RESIZEABLE_FRAME
    log(DEBUG, "borrow: which=%d, pc=%0.2f%%, amount=%0.2f%%", which, pc, amount);
#endif

    if (amount > 0)
    {
        float grow = 0.0;

        // Can we grow?
        if (childMajor < childMajorMax)
        {
            // Yes we can!
            float maxPC = (childMajorMax / major) * 100.0;
            grow = amount;
            if (grow > (maxPC - pc))
            {
                grow = maxPC - pc;
            }
#ifdef DEBUG_RESIZEABLE_FRAME
            log(DEBUG, "borrow:  -> Can grow! maxPC=%0.2f, grow=%0.2f%%", maxPC, grow);
#endif
            m_sizes[which] += grow;
        }

        if (grow != amount)
        {
            // Check neighbour
            grow += borrow(which + direction, amount - grow, major, direction);
        }

        return grow;
    }
    else
    {
        float shrink = 0.0;

        // Can we shrink?
        if (childMajor > childMajorMin)
        {
            // Yes we can!
            float minPC = (childMajorMin / major) * 100.0;
            shrink = -amount;
            if (shrink > (pc - minPC))
            {
                shrink = pc - minPC;
            }
#ifdef DEBUG_RESIZEABLE_FRAME
            log(DEBUG, "borrow:  -> Can shrink! minPC=%0.2f, shrink=%0.2f%%", minPC, shrink);
#endif
            m_sizes[which] -= shrink;

        }
        if (shrink != -amount)
        {
            // Check neighbour
#ifdef DEBUG_RESIZEABLE_FRAME
            log(DEBUG, "borrow:  -> Still got %0.2f%% to go, Checking neighbour", amount - shrink);
#endif
            float ns = borrow(which + direction, amount - shrink, major, direction);
#ifdef DEBUG_RESIZEABLE_FRAME
            log(DEBUG, "borrow:  -> Neighbour shrunk by %0.2f%%", ns);
#endif
            shrink += -ns;
        }
        return -shrink;
    }
}

Widget* ResizeableFrame::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        if (!m_dragging)
        {
            for (Widget* child : m_children)
            {
                if (child->intersects(x, y))
                {
                    return child->handleEvent(event);
                }
            }

            int padding = (int)getStyle("padding-left").asInt();

            // Is the mouse pointer between children?
            int pos;
            vector<Widget*>::iterator it;
            for (it = m_children.begin(), pos = 0; (it + 1) != m_children.end(); ++it, pos++)
            {
                Widget* child = *it;
                Vector2D childPos = child->getAbsolutePosition();
                int width = child->getWidth();
                int height = child->getHeight();
                if ((m_horizontal && (x > childPos.x + width && x < childPos.x + width + padding)) ||
                    (!m_horizontal && (y > childPos.y + height && y < childPos.y + height + padding)))
                {
                    if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON && ((MouseButtonEvent*)event)->direction)
                    {
                        log(DEBUG, "handleMessage: Starting resize!");
                        m_dragging = true;
                        m_dragWidget = pos;
                        Vector2D thisPos = getAbsolutePosition();
                        if (m_horizontal)
                        {
                            m_dragPos = x - thisPos.x;
                        }
                        else
                        {
                            m_dragPos = y - thisPos.y;
                        }

                        FrontierWindow* window = getWindow();
                        if (window != NULL)
                        {
                            window->setMotionWidget(this);
                        }
                    }

                    // This is our area
                    return this;
                }
            }
        }
        else
        {
            if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON && !((MouseButtonEvent*)event)->direction)
            {
                log(DEBUG, "handleMessage: Stopping resize!");

                m_dragging = false;
                if (event->window != NULL)
                {
                    event->window->setMotionWidget(NULL);
                }
            }
            else
            {
                Vector2D thisPos = getAbsolutePosition();
                float pc;
                int pos;
                if (m_horizontal)
                {
                    pos = x - thisPos.x;
                    int diff = m_dragPos - pos;
                    pc = (((float)diff / (float)getWidth()) * 100.0);
                }
                else
                {
                    pos = y - thisPos.y;
                    int diff = m_dragPos - pos;
                    pc = (((float)diff / (float)getHeight()) * 100.0);
                }

#if 0
                log(DEBUG, "handleMessage: diff=%d, pc=%0.2f", diff, pc);
#endif
                m_sizes[m_dragWidget] -= pc;
                m_sizes[m_dragWidget + 1] += pc;
                setDirty(DIRTY_CONTENT | DIRTY_SIZE);

                m_dragPos = pos;
            }
            return NULL;
        }
    }

    return NULL;
}

