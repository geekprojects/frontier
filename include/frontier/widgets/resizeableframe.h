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

#ifndef __FRONTIER_WIDGETS_RESIZEABLE_FRAME_H_
#define __FRONTIER_WIDGETS_RESIZEABLE_FRAME_H_

#include <frontier/widgets/frame.h>

namespace Frontier
{

/**
 * \brief A layout Widget that allows a user to control the size of its children
 *
 * \ingroup widgets
 */
class ResizeableFrame : public Frame
{
 protected:
    std::vector<float> m_sizes;

    // Dragging resize state
    bool m_dragging;
    int m_dragWidget;
    int m_dragPos;

    virtual void layout();

    float borrow(bool horizontal, int which, float amount, int major, int direction);

 public:
    ResizeableFrame(FrontierApp* ui);
    ResizeableFrame(FrontierApp* ui, bool horizontal);
    ResizeableFrame(FrontierWindow* ui, bool horizontal);
    virtual ~ResizeableFrame();

    virtual void add(Widget* widget);
    virtual void addWithSize(Widget* widget, int setPc);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual Frontier::WindowCursor getCursor()
    {
        if (getProperty(FRONTIER_PROP_HORIZONTAL).asBool())
        {
            return Frontier::CURSOR_RESIZE_HORIZONTAL;
        }
        else
        {
            return Frontier::CURSOR_RESIZE_VERTICAL;
        }
    }
};

};

#endif
