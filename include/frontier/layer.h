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

#ifndef __FRONTIER_LAYER_H_
#define __FRONTIER_LAYER_H_

#include <frontier/types.h>
#include <frontier/utils.h>
#include <frontier/object.h>
#include <frontier/app.h>
#include <geek/gfx-surface.h>

namespace Frontier {

class Widget;
class FrontierWindow;

class Layer : public FrontierObject, Geek::Logger
{
 private:
    FrontierApp* m_app;
    bool m_primary;
    bool m_modal;
    FrontierWindow* m_window;
    Widget* m_root;
    Geek::Gfx::Surface* m_surface;

    HorizontalAlign m_horizontalAlign;
    VerticalAlign m_verticalAlign;
    Frontier::Rect m_rect;

 public:
    Layer(FrontierApp* app, bool primary = false);
    virtual ~Layer();

    bool isPrimary() { return m_primary; }
    void setModal(bool modal);
    bool isModal() { return m_modal; }

    void setWindow(FrontierWindow* window);
    void setContentRoot(Widget* root);
    Widget* getContentRoot() { return m_root; }
    Geek::Gfx::Surface* getSurface() { return m_surface; }
    void setSurface(Geek::Gfx::Surface* surface) { m_surface = surface; }

    void setHorizontalAlign(HorizontalAlign ha) { m_horizontalAlign = ha; }
    HorizontalAlign getHorizontalAlign() { return m_horizontalAlign; }
    void setVerticalAlign(VerticalAlign va) { m_verticalAlign = va; }
    VerticalAlign getVerticalAlign() { return m_verticalAlign; }
    
    void setRect(Frontier::Rect rect) { m_rect = rect; }
    Frontier::Rect getRect() { return m_rect; }
    void setSize(Size size) { m_rect.width = size.width; m_rect.height = size.height; }

    bool update();
};

};

#endif
