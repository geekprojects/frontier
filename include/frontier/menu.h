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

class MenuItem
{
 private:
    std::wstring m_title;
    std::vector<MenuItem*> m_children;

    void* m_enginePrivate;

    sigc::signal<void> m_clickSignal;

 public:
    MenuItem(std::wstring title);
    virtual ~MenuItem();

    void setTitle(std::wstring title) { m_title = title; }
    std::wstring getTitle() { return m_title; }

    void add(MenuItem* child) { m_children.push_back(child); }
    std::vector<MenuItem*>& getChildren() { return m_children; }

    virtual sigc::signal<void> clickSignal() { return m_clickSignal; }

    void setEnginePrivate(void* priv) { m_enginePrivate = priv; }
    void* getEnginePrivate() { return m_enginePrivate; }
};

};

#endif
