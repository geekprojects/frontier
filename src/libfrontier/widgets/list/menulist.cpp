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

MenuList::MenuList(FrontierApp* ui, Menu* menu, bool horizontal) : List(ui, horizontal)
{
    if (menu != NULL)
    {
        m_menuItems = menu->getMenuItems();
    }
}

MenuList::MenuList(FrontierWindow* window, Menu* menu, bool horizontal) : List(window, horizontal)
{
    if (menu != NULL)
    {
        m_menuItems = menu->getMenuItems();
    }
}

MenuList::MenuList(FrontierApp* ui, std::vector<MenuItem*> menu, bool horizontal) : List(ui, horizontal)
{
    m_menuItems = menu;
}

MenuList::MenuList(FrontierWindow* window, std::vector<MenuItem*> menu, bool horizontal) : List(window, horizontal)
{
    m_menuItems = menu;
}

MenuList::~MenuList()
{
}

void MenuList::init()
{
    setMenu(m_menuItems);

    selectSignal().connect(sigc::mem_fun(*this, &MenuList::onSelect));
}

void MenuList::calculateSize()
{
    if (m_menuItems.empty())
    {
        m_minSize.set(0, 0);
        if (isHorizontal())
        {
            m_maxSize.set(WIDGET_SIZE_UNLIMITED, 0);
        }
        else
        {
            m_maxSize.set(0, WIDGET_SIZE_UNLIMITED);
        }
        return;
    }

    List::calculateSize();

    if (isHorizontal())
    {
        m_maxSize.height = m_minSize.height;
    }
    else
    {
        m_maxSize.width = m_minSize.width;
    }

}

void MenuList::setMenu(std::vector<MenuItem*> menuItems)
{
    m_menuItems = menuItems;

    clearItems();

    for (MenuItem* menuItem : m_menuItems)
    {
        TextListItem* item = new TextListItem(m_app, menuItem->getTitle());
        item->setPrivateData(menuItem);
        addItem(item);
    }
}

void MenuList::onSelect(ListItem* item)
{
    log(DEBUG, "onSelect: item=%p", item);
    if (item == NULL)
    {
        // Shouldn't happen?
        return;
    }

    clearSelected(item);

    MenuItem* menuItem = (MenuItem*)(item->getPrivateData());

    if (menuItem->getChildren().empty())
    {
        menuItem->clickSignal().emit(menuItem);
    }
    else
    {
        if (getWindow() != NULL)
        {
            Menu* menu = new Menu(menuItem->getChildren());
            Vector2D pos = item->getAbsolutePosition();
            pos.y += m_setSize.height;
            getWindow()->openContextMenu(pos, menu);
        }
    }
}

