
#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include <stdio.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

ResizeableFrame::ResizeableFrame(FrontierApp* ui, bool horizontal) : Frame(ui, horizontal)
{
    m_dragging = false;
    m_dragWidget = 0;
}

ResizeableFrame::ResizeableFrame(FrontierWindow* window, bool horizontal) : Frame(window, horizontal)
{
    m_dragging = false;
    m_dragWidget = 0;
}

ResizeableFrame::~ResizeableFrame()
{
}

void ResizeableFrame::add(Widget* widget)
{
    m_children.push_back(widget);

    widget->setParent(this);
    widget->setDirty();

    m_sizes.clear();

    float pc = 100.0 / (float)m_children.size();

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        m_sizes.push_back(pc);
    }
}

void ResizeableFrame::layout()
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


    // HACK HACK HACK - Do it twice
    int round;
    for (round = 0; round < 2; round++)
    {

    int shrinkable = 0;
    float shrinkpc = 0;

        vector<Widget*>::iterator it;
        int i;

        // Sanity check out sizes
        float total = 0;
        for (float pc : m_sizes)
        {
            total += pc;
        }
        if (total > 100)
        {
            shrinkpc = total - 100; 
        }

        // First, work out if we have any children that need their allocation increasing
        // and which can have theirs shrunk
        for (it = m_children.begin(), i = 0; it != m_children.end(); it++, i++)
        {
            Widget* child = *it;
            Size childMinSize = child->getMinSize();
            Size childMaxSize = child->getMaxSize();

            int childMajorMin = childMinSize.get(m_horizontal);
            int childMajorMax = childMaxSize.get(m_horizontal);

            float pc = m_sizes.at(i);
            int childMajor = (int)((float)major * (pc / 100.0));

            printf("ResizeableFrame::layout: pc=%0.2f, childMajor=%d, minSize=%d, maxSize=%d\n", pc, childMajor, childMajorMin, childMajorMax);
            if (childMajor < childMajorMin)
            {
                int under = childMajorMin - childMajor;
                childMajor = childMajorMin;
                float extrapc = (((float)under / (float)major) * 100.0);
                m_sizes[i] += extrapc;
                shrinkpc += extrapc;
            }
/*
            else if (childMajor > childMajorMax)
            {
                int over = childMajorMax - childMajor;
                childMajor = childMajorMax;
                float extrapc = (((float)over / (float)major) * 100.0);
                m_sizes[i] -= extrapc;
                shrinkpc -= extrapc;
            }
*/
            else
            {
                shrinkable++;
            }

        }
        printf("ResizeableFrame::layout: shrinkable=%d, shrinkpc=%0.2f\n", shrinkable, shrinkpc);

        int majorPos = m_margin;
        int minorPos = m_margin;

        for (it = m_children.begin(), i = 0; it != m_children.end(); it++, i++)
        {
            Widget* child = *it;
            Size childMinSize = child->getMinSize();
            Size childMaxSize = child->getMaxSize();

            int childMajorMin = childMinSize.get(m_horizontal);
            int childMajorMax = childMaxSize.get(m_horizontal);
            float pc = m_sizes.at(i);
            int childMajor = (int)((float)major * (pc / 100.0));

            int childMinor = minor;

            printf("ResizeableFrame::layout:  -> pc=%0.2f, shrinkable=%d, shrinkpc=%0.2f\n", pc, shrinkable, shrinkpc);
            if ((childMajor < childMajorMax) && (childMajor > childMajorMin) && shrinkpc > 0 && shrinkable > 0)
            {
                float s = shrinkpc / shrinkable;
                shrinkpc -= s;
                shrinkable--;

                childMajor -= s;
                if (childMajor > childMajorMax)
                {
                    int over = childMajor - childMajorMax;
                    int extrapc = (int)(((float)over / (float)major) * 100.0);
                    s -= over;
                    childMajor -= over;
                    shrinkpc += extrapc;
                }
                m_sizes[i] -= s;
                printf("ResizeableFrame::layout:    -> Shrunk by %0.2f%%\n", s);
            }

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
}

Widget* ResizeableFrame::handleMessage(Message* msg)
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

            if (!m_dragging)
            {
                vector<Widget*>::iterator it;
                for (it = m_children.begin(); it != m_children.end(); it++)
                {
                    Widget* child = *it;
                    if (child->intersects(x, y))
                    {
                        return child->handleMessage(msg);
                    }
                }

                if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON &&
                    imsg->event.button.direction)
                {
                    int pos;
                    for (it = m_children.begin(), pos = 0; (it + 1) != m_children.end(); it++, pos++)
                    {
                        Widget* child = *it;
                        Vector2D childPos = child->getAbsolutePosition();
                        int width = child->getWidth();
                        if (x > childPos.x + width && x < childPos.x + width + m_padding)
                        {
                            printf("ResizeableFrame::handleMessage: Starting resize!\n");
                            m_dragging = true;
                            m_dragWidget = pos;
                            Vector2D thisPos = getAbsolutePosition();
                            m_dragPos = x - thisPos.x;

                            if (imsg->window != NULL)
                            {
                                imsg->window->setDragWidget(this);
                            }

                            return this;
                        }
                    }
                }

                if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
                {
                    return this;
                }
            }
            else
            {
                if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON &&
                    !imsg->event.button.direction)
                {
                    printf("ResizeableFrame::handleMessage: Stopping resize!\n");

                    m_dragging = false;
                    if (imsg->window != NULL)
                    {
                        imsg->window->setDragWidget(NULL);
                    }
                }
                else
                {
                    Vector2D thisPos = getAbsolutePosition();
                    x -= thisPos.x;
                    int diff = m_dragPos - x;

                    float pc = (((float)diff / (float)getWidth()) * 100.0);
#if 0
                    printf("ResizeableFrame::handleMessage: diff=%d, pc=%0.2f\n", diff, pc);
#endif
                    m_sizes[m_dragWidget] -= pc;
                    m_sizes[m_dragWidget + 1] += pc;
                    setDirty();

                    m_dragPos = x;
                }
                return this;
            }
        }
    }

    return NULL;
}

