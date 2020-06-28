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

#ifndef __FRONTIER_WIDGETS_SCROLLER_H_
#define __FRONTIER_WIDGETS_SCROLLER_H_

#include <frontier/widgets.h>
#include <frontier/widgets/scrollbar.h>

namespace Frontier
{

/**
 * \brief A Widget that provides a view of a larger Widget hierarchy
 *
 * \ingroup widgets
 */
class Scroller : public Widget
{
 private:
    ScrollBar* m_hScrollBar;
    ScrollBar* m_vScrollBar;
    Widget* m_child;
    Geek::Gfx::Surface* m_childSurface;
    Size m_drawSize;

    void checkSurfaceSize(bool highDPI);
    int getWidthOverhead() { return (m_vScrollBar->getWidth() - 2); }

    void initScroller(Widget* child);

 public:
    Scroller(FrontierApp* ui);
    Scroller(FrontierApp* ui, Widget* child);
    Scroller(FrontierWindow* ui);
    Scroller(FrontierWindow* ui, Widget* child);
    virtual ~Scroller();

    virtual void calculateSize();
    virtual void layout();
    //virtual void setWidth(int width);

    int getPos() { return m_vScrollBar->getPos(); }

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void setChild(Widget* child);

    virtual void dump(int level);
};

};

#endif
