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


#include <frontier/contextmenu.h>
#include <frontier/widgets/list.h>
#include <frontier/widgets/frame.h>

using namespace std;
using namespace Frontier;
using namespace Geek;


ContextMenu::ContextMenu(FrontierApp* app) : FrontierWindow(app, L"", 0)
{
    m_menu = NULL;
    m_menuList = NULL;
}

ContextMenu::~ContextMenu()
{
}

bool ContextMenu::init()
{
    Frame* frame = new Frame(getApp(), false);

    m_menuList = new MenuList(getApp(), m_menu);
    m_menuList->selectSignal().connect(sigc::mem_fun(*this, &ContextMenu::itemSelected));
    frame->add(m_menuList);

    setContent(frame);

    return true;
}

void ContextMenu::setMenu(Menu* menu)
{
    if (m_menuList == NULL)
    {
        init();
    }

    m_menu = menu;
    if (m_menu == NULL)
    {
        m_menuList->clearItems();
        return;
    }

    m_menuList->setMenu(m_menu->getMenuItems());
}

void ContextMenu::lostFocus()
{
    hide();
}

void ContextMenu::itemSelected(ListItem* item)
{
    MenuItem* menuItem = (MenuItem*)(item->getPrivateData());
    log(DEBUG, "itemSelected: %ls", menuItem->getTitle().c_str());

    menuItem->clickSignal().emit(menuItem);

    hide();
}

