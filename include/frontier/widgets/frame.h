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

#ifndef __FRONTIER_WIDGETS_FRAME_H_
#define __FRONTIER_WIDGETS_FRAME_H_

#include <frontier/widgets.h>

#define FRONTIER_PROP_HORIZONTAL L"horizontal"

namespace Frontier
{

/**
 * \brief Groups widgets together vertically or horizontally
 *
 * \ingroup widgets
 */
class Frame : public Widget
{
 public:
    explicit Frame(FrontierApp* ui);
    Frame(FrontierApp* ui, bool horizontal);
    Frame(FrontierApp* ui, std::wstring widgetName, bool horizontal);
    ~Frame() override;

    void add(Widget* widget) override;
    void remove(Widget* widget) override;

    void calculateSize() override;
    void layout() override;

    bool draw(Geek::Gfx::Surface* surface) override;

    Widget* handleEvent(Frontier::Event* event) override;

    void activateNext(Widget* activeChild) override;
};

/**
 * \brief Groups widgets together horizontally
 *
 * \ingroup widgets
 */
class HFrame : public Frame
{
 public:
    explicit HFrame(FrontierApp* ui) : Frame(ui, true) {}
    ~HFrame() override = default;
};

/**
 * \brief Groups widgets together vertically
 *
 * \ingroup widgets
 */
class VFrame : public Frame
{
 public:
    explicit VFrame(FrontierApp* ui) : Frame(ui, false) {}
    ~VFrame() override = default;
};

}

#endif
