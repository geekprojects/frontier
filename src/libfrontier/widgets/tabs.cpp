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
#include <frontier/widgets/tabs.h>
#include <frontier/fontawesome.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define MAX_TAB_SIZE 250
#define TAB_SIZE 22

Tabs::Tabs(FrontierApp* ui) : Widget(ui, L"Tabs")
{
    m_activeTab = 0;
    m_collapsible = false;
    m_collapsed = false;
    m_placement = TAB_TOP;
}

Tabs::Tabs(FrontierApp* ui, bool collapsible, TabPlacement placement) : Widget(ui, L"Tabs")
{
    m_activeTab = 0;
    m_collapsible = collapsible;
    m_collapsed = false;
    m_placement = placement;
}

Tabs::Tabs(FrontierWindow* window) : Widget(window, L"Tabs")
{
    m_activeTab = 0;
    m_collapsible = false;
    m_collapsed = false;
    m_placement = TAB_TOP;
}

Tabs::Tabs(FrontierWindow* window, bool collapsible, TabPlacement placement) : Widget(window, L"Tabs")
{
    m_activeTab = 0;
    m_collapsible = collapsible;
    m_collapsed = false;
    m_placement = placement;
}

Tabs::~Tabs()
{
    for (Tab tab : m_tabs)
    {
        tab.content->decRefCount();
    }
    m_tabs.clear();
}

void Tabs::init()
{
    Menu* menu = new Menu();

    MenuItem* closeItem = new MenuItem(L"Close");
    closeItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeActiveTab));
    menu->add(closeItem);

    MenuItem* closeAllItem = new MenuItem(L"Close All");
    closeAllItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeAllTabs));
    menu->add(closeAllItem);

    MenuItem* closeOthersItem = new MenuItem(L"Close Others");
    closeOthersItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeAllButActiveTab));
    menu->add(closeOthersItem);

    setContextMenu(menu);
}

void Tabs::calculateSize()
{
    if (m_tabs.empty() || (m_collapsible && m_collapsed))
    {
        if (isHorizontal())
        {
            m_minSize.set(0, TAB_SIZE);
            m_maxSize.set(WIDGET_SIZE_UNLIMITED, TAB_SIZE);
        }
        else
        {
            m_minSize.set(TAB_SIZE, 0);
            m_maxSize.set(TAB_SIZE, WIDGET_SIZE_UNLIMITED);
        }
        return;
    }

    Widget* activeWidget = getActiveTab();
    if (activeWidget == NULL)
    {
        return;
    }

    activeWidget->calculateSize();

    Size activeMinSize = activeWidget->getMinSize();
    Size activeMaxSize = activeWidget->getMaxSize();

    if (isHorizontal())
    {
        activeMinSize.height += TAB_SIZE;

        activeMaxSize.width = WIDGET_SIZE_UNLIMITED;
        activeMaxSize.height += TAB_SIZE;
    }
    else
    {
        activeMinSize.width += TAB_SIZE;

        activeMaxSize.width += TAB_SIZE;
        activeMaxSize.height = WIDGET_SIZE_UNLIMITED;
    }

    m_minSize = activeMinSize;
    m_maxSize = activeMaxSize;

    int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
    int tabsWidth = 0;
    for (Tab tab : m_tabs)
    {
        tabsWidth += 20;
        if (tab.closeable)
        {
            tabsWidth += closeWidth;
        }
    }

    if (isHorizontal())
    {
        if (m_minSize.width < tabsWidth)
        {
            m_minSize.width = tabsWidth;
        }
    }
    else
    {
        if (m_minSize.height < tabsWidth)
        {
            m_minSize.height = tabsWidth;
        }
    }
}

void Tabs::layout()
{
    if (m_tabs.empty())
    {
        return;
    }

    if (!m_collapsible || !m_collapsed)
    {
        Widget* activeWidget = getActiveTab();

        Rect contentRect = getContentRect();

        activeWidget->setSize(Size(contentRect.width, contentRect.height));
        activeWidget->setPosition(contentRect.x, contentRect.y);
        activeWidget->layout();
    }
}

bool Tabs::draw(Surface* surface)
{
    Rect tabsRect = getTabsRect();

    int labelHeight = m_app->getTheme()->getTextHeight();

    //surface->clear(0x0);

    m_app->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        STATE_NONE,
        tabsRect.x, tabsRect.y,
        tabsRect.width, tabsRect.height);

    if (!m_tabs.empty() && m_activeTab >= m_tabs.size())
    {
        log(ERROR, "draw: Invalid active tab: %d", m_activeTab);
        m_activeTab = m_tabs.size() - 1;
    }

    Size tabSize = getTabSize();

#if 0
    log(DEBUG, "draw: tabs=%lu", m_tabs.size());
#endif

    int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);

    int labelY = ((TAB_SIZE / 2) - (labelHeight / 2));

    vector<Tab>::iterator it;
    int x = tabsRect.x;
    int y = tabsRect.y;

    if (m_collapsible)
    {
        int icon;
        if (m_collapsed)
        {
            switch (m_placement)
            {
                case TAB_TOP:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_UP;
                    break;
                case TAB_BOTTOM:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_DOWN;
                    break;
                case TAB_LEFT:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_LEFT;
                    break;
                case TAB_RIGHT:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_RIGHT;
                    break;
            }
        }
        else
        {
            switch (m_placement)
            {
                case TAB_TOP:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_DOWN;
                    break;
                case TAB_BOTTOM:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_UP;
                    break;
                case TAB_LEFT:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_RIGHT;
                    break;
                case TAB_RIGHT:
                    icon = FRONTIER_ICON_ANGLE_DOUBLE_LEFT;
                    break;
            }

        }

        m_app->getTheme()->drawIcon(
            surface,
            tabsRect.x,
            tabsRect.y,
            icon,
            false);
 
        if (isHorizontal())
        {
            x += TAB_SIZE;
        }
        else
        {
            y += TAB_SIZE;
        }
    }

    int rotate = 0;
    if (m_placement == TAB_LEFT)
    {
        rotate = 90;
    }
    else if (m_placement == TAB_RIGHT)
    {
        rotate = 270;
    }

    unsigned int tab;
    for (it = m_tabs.begin(), tab = 0; it != m_tabs.end(); it++, tab++)
    {
        //uint32_t backgroundCol;
        bool isActive = (tab == m_activeTab);
        UIState state = STATE_NONE;
        if (isActive)
        {
            //backgroundCol = 0xff808080;
            state = STATE_SELECTED;
        }
        else
        {
            //backgroundCol = m_app->getTheme()->getColour(COLOUR_WINDOW_BACKGROUND);
        }

#if 0
        log(DEBUG, "draw: %d,%d, width=%d, height=%d", x, y, tabSize.width, tabSize.height);
#endif

        m_app->getTheme()->drawBorder(
            surface,
            BORDER_TAB,
            state,
            x, y,
            tabSize.width, tabSize.height);

        int titleWidth;
if (isHorizontal())
{
        titleWidth = tabSize.width - 10;
}
else
{
        titleWidth = tabSize.height - 10;
}
        if (it->closeable)
        {
            titleWidth -= closeWidth + 5;
        }

#if 1
        log(DEBUG, "draw:  -> %ls: active=%d titleWidth=%d, closeable=%d", it->title.c_str(), isActive, titleWidth, it->closeable);
#endif

        m_app->getTheme()->drawText(
            surface,
            x + 5,
            labelY + y,
            it->title.c_str(),
            titleWidth, false, rotate); 

        if (it->closeable)
        {
            m_app->getTheme()->drawIcon(
                surface,
                x + tabSize.width - (closeWidth + 5),
                labelY + y,
                FRONTIER_ICON_WINDOW_CLOSE,
                false);
        }

        if (isHorizontal())
        {
            x += tabSize.width;
        }
        else
        {
            y += tabSize.height;
        }
    }

    if (!m_tabs.empty() && (!m_collapsible || !m_collapsed))
    {
        Widget* activeWidget = m_tabs.at(m_activeTab).content;
        if (activeWidget != NULL)
        {
            SurfaceViewPort viewport(
                surface,
                activeWidget->getX(),
                activeWidget->getY(),
                activeWidget->getWidth(),
                activeWidget->getHeight());
            return activeWidget->draw(&viewport, Rect(0, 0, activeWidget->getWidth(), activeWidget->getHeight()));
        }
    }

    return true;
}

Widget* Tabs::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        Vector2D thisPos = getAbsolutePosition();
        x -= thisPos.x;
        y -= thisPos.y;

        Rect tabsRect = getTabsRect();

        if (tabsRect.intersects(x, y))
        {
            if (event->eventType != FRONTIER_EVENT_MOUSE_BUTTON)
            {
                return this;
            }

            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;

            x -= tabsRect.x;
            y -= tabsRect.y;

            int tabPos;
            if (isHorizontal())
            {
               tabPos = x;
            }
            else
            {
               tabPos = y;
            }
 
            if (m_collapsible)
            {
                if (tabPos < TAB_SIZE)
                {
                     if (mouseButtonEvent->direction)
                     {
                         m_collapsed = !m_collapsed;
                         setDirty();
                    }
                    return this;
                }
                tabPos -= TAB_SIZE;
            }

            if (m_tabs.empty())
            {
                return this;
            }

            Size tabSize = getTabSize();
            unsigned int tab = 0;

            if (isHorizontal())
            {
                if (tabSize.width > 0)
                {
                    tab = tabPos / tabSize.width;
                }
            }
            else
            {
                if (tabSize.height > 0)
                {
                    tab = tabPos / tabSize.height;
                }
            }

#if 0
            log(DEBUG, "handleMessage: x=%d, m_activeTab=%d", x, m_activeTab);
#endif

            if (tab >= m_tabs.size())
            {
                return this;
            }

            Widget* activeTab = getActiveTab();

            if (m_tabs.at(tab).closeable)
            {
                int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
                if (x > (int)((tab * tabSize.width) + (tabSize.width - (closeWidth + 5))))
                {
                    if (!mouseButtonEvent->direction)
                    {
                        m_closeTabSignal.emit(m_tabs.at(tab).content);
                    }

                    return this;
                }
            }

            if (mouseButtonEvent->buttons == BUTTON_RIGHT)
            {
                log(DEBUG, "handleMessage: CONTEXT MENU!!!");
                openContextMenu(Geek::Vector2D(mouseButtonEvent->x, mouseButtonEvent->y));
            }
            else if (!mouseButtonEvent->direction)
            {
                return NULL;
            }

            m_activeTab = tab;
            activeTab = getActiveTab();
            m_collapsed = false;

            setDirty();

#if 0
            log(DEBUG, "handleMessage: activeTab=%p", activeTab);
#endif

            m_changeTabSignal.emit(activeTab);
            if (activeTab != NULL)
            {
                activeTab->setDirty();
                return activeTab;
            }
            else
            {
                return this;
            }
        }
        else if (!m_tabs.empty())
        {
            Widget* activeWidget = m_tabs.at(m_activeTab).content;

            if (activeWidget != NULL)
            {
                return activeWidget->handleEvent(event);
            }
        }
        return this;
    }
    return NULL;
}

void Tabs::addTab(std::wstring title, Widget* content, bool closeable)
{
    Tab tab;
    tab.title = title;
    tab.content = content;
    tab.closeable = closeable;

    m_tabs.push_back(tab);

    content->incRefCount();
    content->setParent(this);

    setDirty();
}

void Tabs::closeTab(Widget* widget, bool emitChangeSignal)
{
    vector<Tab>::iterator it;

    unsigned int i;
    for (i = 0, it = m_tabs.begin(); it != m_tabs.end(); it++, i++)
    {
        if (it->content == widget)
        {
            bool isActive = (i == m_activeTab);

            it->content->decRefCount();
            m_tabs.erase(it);

            if (m_activeTab >= m_tabs.size())
            {
                m_activeTab = m_tabs.size() - 1;
            }

            if (isActive && emitChangeSignal)
            {
                m_changeTabSignal.emit(getActiveTab());
            }

            layout();
            setDirty();
            return;
        }
    }
}

void Tabs::closeActiveTab()
{
    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        closeTab(activeWidget);
    }
}

void Tabs::closeAllTabs()
{
    vector<Tab> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab tab : tabs)
    {
        if (tab.closeable)
        {
            closeTab(tab.content, false);
        }
    }
}

void Tabs::closeAllButActiveTab()
{
    Widget* activeWidget = getActiveTab();

    vector<Tab> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab tab : tabs)
    {
        if (tab.closeable && tab.content != activeWidget)
        {
            closeTab(tab.content, false);
        }
    }
}

void Tabs::setActiveTab(Widget* tabContent)
{
    int i = 0;
    for (Tab tab : m_tabs)
    {
        if (tab.content == tabContent)
        {
            m_activeTab = i;

            layout();
            setDirty();
            return;
        }
        i++;
    }

    return;
}

int Tabs::findTab(Widget* tabContent)
{
    int i = 0;
    for (Tab tab : m_tabs)
    {
        if (tab.content == tabContent)
        {
            return i;
        }
        i++;
    }

    // Not found
    return -1;
}

void Tabs::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }
    log(DEBUG, "%sTabs(%p): x=%d, y=%d, size=%s", spaces.c_str(), this, m_x, m_y, m_setSize.toString().c_str());

    for (Tab tab : m_tabs)
    {
        tab.content->dump(level + 1);
    }

/*
    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        activeWidget->dump(level + 1);
    }
*/
}

Size Tabs::getTabSize()
{
    if (m_tabs.empty())
    {
        return Size(0, 0);
    }

    int major;
    if (isHorizontal())
    {
        major = m_setSize.width;
    }
    else
    {
        major = m_setSize.height;
    }

    if (m_collapsible)
    {
        major -= TAB_SIZE;
    }

    int tabMajor = major / m_tabs.size();
    if (tabMajor > MAX_TAB_SIZE)
    {
        tabMajor = MAX_TAB_SIZE;
    }

    Size size;
    if (isHorizontal())
    {
        size.width = tabMajor;
        size.height = TAB_SIZE;
    }
    else
    {
        size.width = TAB_SIZE;
        size.height = tabMajor;
    }

    return size;
}

Frontier::Rect Tabs::getTabsRect()
{
    Rect r;

    r.x = 0;
    r.y = 0;

    if (isHorizontal())
    {
        r.width = m_setSize.width;
        r.height = TAB_SIZE;
    }
    else
    {
        r.width = TAB_SIZE;
        r.height = m_setSize.height;
    }

    switch (m_placement)
    {
        case TAB_TOP:
            break;

        case TAB_BOTTOM:
            r.y = m_setSize.height - TAB_SIZE;
            break;

        case TAB_LEFT:
            break;

        case TAB_RIGHT:
            r.x = m_setSize.width - TAB_SIZE;
            break;
    }

    return r;
}

Frontier::Rect Tabs::getContentRect()
{
    Rect r;

    r.x = 0;
    r.y = 0;

    if (isHorizontal())
    {
        r.width = m_setSize.width;
        r.height = m_setSize.height - TAB_SIZE;
    }
    else
    {
        r.width = m_setSize.width - TAB_SIZE;
        r.height = m_setSize.height;
    }

    switch (m_placement)
    {
        case TAB_TOP:
	    r.y = TAB_SIZE;
            break;

        case TAB_BOTTOM:
            break;

        case TAB_LEFT:
	    r.x = TAB_SIZE;
            break;

        case TAB_RIGHT:
            break;
    }
    return r;
}

