/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
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
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

MenuList::MenuList(FrontierApp* ui, Menu* menu) : List(ui)
{
    if (menu != NULL)
    {
        m_menuItems = menu->getMenuItems();
    }
}

MenuList::MenuList(FrontierWindow* window, Menu* menu) : List(window)
{
    if (menu != NULL)
    {
        m_menuItems = menu->getMenuItems();
    }
}

MenuList::MenuList(FrontierApp* ui, std::vector<MenuItem*> menu) : List(ui)
{
    m_menuItems = menu;
}

MenuList::MenuList(FrontierWindow* window, std::vector<MenuItem*> menu) : List(window)
{
    m_menuItems = menu;
}

MenuList::~MenuList()
{
}

void MenuList::init()
{
    setMenu(m_menuItems);
}

void MenuList::setMenu(std::vector<MenuItem*> menuItems)
{
printf("MenuList::setMenu: Here!\n");
printf("MenuList::setMenu: items=%lu\n", menuItems.size());
    m_menuItems = menuItems;

printf("MenuList::setMenu: Clearing...\n");
    clearItems();
printf("MenuList::setMenu: Adding...\n");
    for (MenuItem* menuItem : m_menuItems)
    {
printf("MenuList::setMenu: Adding item: %ls\n", menuItem->getTitle().c_str());
        TextListItem* item = new TextListItem(m_app, menuItem->getTitle());
        item->setPrivateData(menuItem);
        addItem(item);
    }
printf("MenuList::setMenu: Done\n");
}


