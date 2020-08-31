/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
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
#include <frontier/widgets.h>
#include <frontier/contextmenu.h>

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

//map<std::string, WidgetInit*> WidgetRegistry::m_widgets;
//

static WidgetRegistry* g_widgetRegistry = NULL;

WidgetRegistry::WidgetRegistry()
{
}

WidgetRegistry::~WidgetRegistry()
{
}

void WidgetRegistry::registerWidget(WidgetInit* init)
{
if (g_widgetRegistry == NULL)
{
g_widgetRegistry = new WidgetRegistry();
}
    g_widgetRegistry->m_widgets.insert(make_pair(init->getName(), init));
}

Widget* WidgetRegistry::createWidget(FrontierApp* app, std::string name)
{
    map<std::string, WidgetInit*>::iterator it = g_widgetRegistry->m_widgets.find(name);
    if (it != g_widgetRegistry->m_widgets.end())
    {
        WidgetInit* init = it->second;
        return init->create(app);
    }
    return NULL;
}

