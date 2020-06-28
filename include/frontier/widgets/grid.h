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

#ifndef __FRONTIER_WIDGETS_GRID_H_
#define __FRONTIER_WIDGETS_GRID_H_

#include <frontier/widgets.h>

namespace Frontier
{
struct GridItem
{
    int x;
    int y;
    uint32_t background;
    Widget* widget;
};

/**
 * \brief A layout Widget that displays Widgets in a Grid
 *
 * \ingroup widgets
 */
class Grid : public Frontier::Widget
{
 protected:
    std::vector<GridItem*> m_grid;

    int* m_colMinSizes;
    int* m_colMaxSizes;
    int* m_rowMinSizes;
    int* m_rowMaxSizes;

    void freeSizes();
    void clearChildren();

    virtual void calculateSize();
    virtual void layout();

 public:
    Grid(FrontierApp* app);
    Grid(FrontierWindow* window);
    virtual ~Grid();

    virtual void put(int x, int y, Widget* widget);
    virtual void put(int x, int y, Widget* widget, uint32_t background);
    GridItem* getGridItem(int x, int y);
    Widget* getItem(int x, int y);
    Size getGridSize();
    void clear();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
