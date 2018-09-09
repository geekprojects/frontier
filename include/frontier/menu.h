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

namespace Frontier
{

class MenuItem
{
 private:

    sigc::signal<void> m_clickSignal;

 public:
    MenuItem(std::string title);
    virtual ~MenuItem();

    virtual sigc::signal<void> clickSignal() { return m_clickSignal; }
};

class Menu
{
 private:


 public:
    Menu(std::string title);
    virtual ~Menu();
};

};

#endif
