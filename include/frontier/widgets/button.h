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

#ifndef __FRONTIER_WIDGETS_BUTTON_H_
#define __FRONTIER_WIDGETS_BUTTON_H_

#include <frontier/widgets/label.h>

namespace Frontier
{

enum ButtonType
{
    BUTTON_NORMAL,
    BUTTON_TOGGLE
};

/**
 * \brief Simple Button object that response to mouse clicks
 *
 * \ingroup widgets
 */
class Button : public Label
{
 protected:
    ButtonType m_type;
    bool m_emitAll;

 public:
    Button(FrontierApp* ui, std::wstring text, ButtonType type = BUTTON_NORMAL);
    Button(FrontierApp* ui, std::wstring widgetType, std::wstring text, ButtonType type = BUTTON_NORMAL);
    virtual ~Button();

    void setEmitAll(bool emitAll) { m_emitAll = emitAll; }

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
