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


#include <frontier/frontier.h>
#include <frontier/widgets/builder.h>
#include <frontier/widgets/label.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;


WidgetBuilder::WidgetBuilder(FrontierApp* app) : Logger(L"WidgetBuilder")
{
    m_app = app;
}

WidgetBuilder::~WidgetBuilder()
{
}

Widget* WidgetBuilder::loadWidget(const char* filename)
{
    xmlDocPtr doc;
    doc = xmlReadFile(
        filename,
        NULL,
        XML_PARSE_NOCDATA | XML_PARSE_NOBLANKS);

    xmlNode* root = xmlDocGetRootElement(doc);

    return walk(doc, root, NULL);
}

Widget* WidgetBuilder::walk(xmlDoc* doc, xmlNode* node, Widget* parent)
{
    Widget* widget = WidgetRegistry::createWidget(m_app, string((char*)(node->name)));
    log(DEBUG, "walk: Widget: %s = %p", node->name, widget);

if (widget == NULL)
{
return new Label(m_app, L"?");
}

    xmlAttr* attr;
    for (attr = node->properties; attr != NULL; attr = attr->next)
    {
        string name = string((char*)attr->name);
        xmlChar* valueChar = xmlNodeListGetString(doc, attr->children, 1);
        string value = "";
        if (valueChar != NULL)
        {
            value = string((char*)valueChar);
            xmlFree(valueChar);
        }


        if (name == "id")
        {
            log(DEBUG, "walk: Widget: %s: id=%s", node->name, value.c_str());
            widget->setWidgetId(Utils::string2wstring(value));
        }
        else
        {
            log(DEBUG, "walk: Widget: %s: attribute=%s, value=%s", node->name, attr->name, value.c_str());

            widget->setProperty(Utils::string2wstring(name), Value(Utils::string2wstring(value)));
        }
    }

    xmlNode* childNode = NULL;
    for (childNode = node->children; childNode != NULL; childNode = childNode->next)
    {
        if (childNode->type == XML_ELEMENT_NODE)
        {
            Widget* childWidget = walk(doc, childNode, widget);
            widget->add(childWidget);
        }
    }

    return widget;
}

