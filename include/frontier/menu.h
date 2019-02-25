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

#ifndef __FRONTIER_MENU_H_
#define __FRONTIER_MENU_H_

#include <frontier/object.h>

#include <string>
#include <vector>

#include <sigc++/sigc++.h>

namespace Frontier
{

enum MenuType
{
    MENU_TYPE_ABOUT,
    MENU_TYPE_WINDOW,
    MENU_TYPE_HELP,
};

class MenuItem : public FrontierObject
{
 private:
    std::wstring m_title;
    bool m_isSeparator;
    std::vector<MenuItem*> m_children;

    wchar_t m_key;
    uint32_t m_keyModifiers;

    void* m_enginePrivate;

    sigc::signal<void, MenuItem*> m_clickSignal;

 public:
    MenuItem(std::wstring title);
    MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers);
    virtual ~MenuItem();

    void setTitle(std::wstring title) { m_title = title; }
    std::wstring getTitle() { return m_title; }
    void setIsSeparator(bool isSeparator);
    bool getIsSeparator() { return m_isSeparator; }

    wchar_t getKey() { return m_key; }
    wchar_t getKeyModifiers() { return m_keyModifiers; }

    void add(MenuItem* child);
    std::vector<MenuItem*>& getChildren() { return m_children; }

    virtual sigc::signal<void, MenuItem*> clickSignal() { return m_clickSignal; }

    void setEnginePrivate(void* priv) { m_enginePrivate = priv; }
    void* getEnginePrivate() { return m_enginePrivate; }
};

class MenuSeparator : public MenuItem
{
 private:

 public:
    MenuSeparator();
    virtual ~MenuSeparator();
};

class Menu : public FrontierObject
{
 private:
    std::vector<MenuItem*> m_menuItems;

 public:
    Menu();
    ~Menu();

    void add(MenuItem* child) { m_menuItems.push_back(child); }
    std::vector<MenuItem*>& getMenuItems() { return m_menuItems; }
};

};

#endif
