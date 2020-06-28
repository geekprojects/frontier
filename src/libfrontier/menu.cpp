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


#include <frontier/menu.h>

using namespace std;
using namespace Frontier;

Menu::Menu()
{
}

Menu::Menu(vector<MenuItem*> items)
{
    m_menuItems = items;
}

Menu::~Menu()
{
}


MenuItem::MenuItem(std::wstring title)
{
    init(title, 0, 0, false);
}

MenuItem::MenuItem(std::wstring title, sigc::slot<void, MenuItem*> clickSignalSlot)
{
    init(title, 0, 0, false);

    m_clickSignal.connect(clickSignalSlot);
}

MenuItem::MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers)
{
    init(title, key, keyModifiers, false);
}

MenuItem::MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers, sigc::slot<void, MenuItem*> clickSignalSlot)
{
    init(title, key, keyModifiers, false);

    m_clickSignal.connect(clickSignalSlot);
}

MenuItem::~MenuItem()
{
    for (MenuItem* child : m_children)
    {
        delete child;
    }

    m_children.clear();
}

void MenuItem::init(wstring title, wchar_t key, uint32_t keyModifiers, bool isSeparator)
{
    m_title = title;
    m_key = key;
    m_keyModifiers = keyModifiers;
    m_isSeparator = isSeparator;
}

void MenuItem::setIsSeparator(bool isSeparator)
{
    m_isSeparator = isSeparator;
}

void MenuItem::add(MenuItem* child)
{
    m_children.push_back(child);
}

MenuSeparator::MenuSeparator() : MenuItem(L"")
{
    setIsSeparator(true);
}

MenuSeparator::~MenuSeparator()
{
}


