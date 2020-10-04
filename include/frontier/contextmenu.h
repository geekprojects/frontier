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

#ifndef __FRONTIER_CONTEXT_MENU_H_
#define __FRONTIER_CONTEXT_MENU_H_

#include <frontier/frontier.h>
#include <frontier/menu.h>
#include <frontier/widgets/list.h>

#include <vector>

namespace Frontier
{

/**
 * \brief A special Window that displays a Menu
 *
 * \ingroup windows
 */
class ContextMenu : public FrontierWindow
{
 private:
    Menu* m_menu;
    MenuList* m_menuList;

 public:
    explicit ContextMenu(FrontierApp* app);
    ~ContextMenu() override;

    bool init() override;

    void setMenu(Menu* menu) override;

    void lostFocus() override;

    void itemSelected(ListItem* item);
};

}

#endif
