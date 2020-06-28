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

#ifndef __FRONTIER_WIDGETS_SCROLLBAR_H_
#define __FRONTIER_WIDGETS_SCROLLBAR_H_

#include <frontier/widgets.h>

namespace Frontier
{

/**
 * \brief A simple scroll bar Widget
 *
 * \ingroup widgets
 */
class ScrollBar : public Widget
{
 private:
    bool m_horizontal;
    int m_min;
    int m_max;
    int m_pos;
    int m_size;
    bool m_dragging;
    int m_dragOffset;

    int getScaledValue(BoxModel& boxModel, int v);
    int getControlPos(BoxModel& boxModel);
    int getControlSize(BoxModel& boxModel);
    int range() { return m_max - (m_min + m_size); }

    sigc::signal<void, int> m_changedPositionSignal;

 public:
    ScrollBar(FrontierApp* ui, bool horizontal);
    ScrollBar(FrontierWindow* window, bool horizontal);
    virtual ~ScrollBar();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void set(int min, int max, int size);
    void setPos(int pos);
    int getPos();

    virtual sigc::signal<void, int> changedPositionSignal() { return m_changedPositionSignal; }
};

};

#endif
