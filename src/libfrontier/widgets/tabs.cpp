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

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define MAX_TAB_SIZE 250
#define TAB_SIZE 22

Tabs::Tabs(FrontierApp* ui) : Widget(ui, L"Tabs")
{
    m_activeTab = NULL;
    m_collapsible = false;
    m_collapsed = false;
    m_placement = TAB_TOP;
}

Tabs::Tabs(FrontierApp* ui, bool collapsible, TabPlacement placement) : Widget(ui, L"Tabs")
{
    m_activeTab = NULL;
    m_collapsible = collapsible;
    m_collapsed = false;
    m_placement = placement;
}

Tabs::Tabs(FrontierWindow* window) : Widget(window, L"Tabs")
{
    m_activeTab = NULL;
    m_collapsible = false;
    m_collapsed = false;
    m_placement = TAB_TOP;
}

Tabs::Tabs(FrontierWindow* window, bool collapsible, TabPlacement placement) : Widget(window, L"Tabs")
{
    m_activeTab = NULL;
    m_collapsible = collapsible;
    m_collapsed = false;
    m_placement = placement;
}

Tabs::~Tabs()
{
    for (Tab* tab : m_tabs)
    {
        tab->decRefCount();
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

    uint32_t openIcon = 0;
    uint32_t closedIcon = 0;
    switch (m_placement)
    {
        case TAB_TOP:
            openIcon = FRONTIER_ICON_ANGLE_DOUBLE_UP;
            closedIcon = FRONTIER_ICON_ANGLE_DOUBLE_DOWN;
            break;
        case TAB_BOTTOM:
            openIcon = FRONTIER_ICON_ANGLE_DOUBLE_DOWN;
            closedIcon = FRONTIER_ICON_ANGLE_DOUBLE_UP;
            break;
        case TAB_LEFT:
            openIcon = FRONTIER_ICON_ANGLE_DOUBLE_LEFT;
            closedIcon = FRONTIER_ICON_ANGLE_DOUBLE_RIGHT;
            break;
        case TAB_RIGHT:
            openIcon = FRONTIER_ICON_ANGLE_DOUBLE_RIGHT;
            closedIcon = FRONTIER_ICON_ANGLE_DOUBLE_LEFT;
            break;
    }
    m_openIcon = m_app->getTheme()->getIcon(openIcon);
    m_closedIcon = m_app->getTheme()->getIcon(closedIcon);


    dragDropSignal().connect(sigc::mem_fun(*this, &Tabs::onDragDrop));
}

void Tabs::calculateSize()
{
    if (m_tabs.empty() || (m_collapsible && m_collapsed))
    {
        if (isHorizontal())
        {
            m_minSize.set(TAB_SIZE, TAB_SIZE);
            m_maxSize.set(WIDGET_SIZE_UNLIMITED, TAB_SIZE);
        }
        else
        {
            m_minSize.set(TAB_SIZE, TAB_SIZE);
            m_maxSize.set(TAB_SIZE, WIDGET_SIZE_UNLIMITED);
        }
        return;
    }

    Widget* activeWidget = getActiveTab();
    Size activeMinSize(0, 0);
    Size activeMaxSize(0, 0);

    if (activeWidget != NULL)
    {
        activeWidget->calculateSize();

        activeMinSize = activeWidget->getMinSize();
        activeMaxSize = activeWidget->getMaxSize();

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
    }

    m_minSize = activeMinSize;
    m_maxSize = activeMaxSize;

    int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
    int tabsWidth = 0;
    for (Tab* tab : m_tabs)
    {
        tabsWidth += TAB_SIZE * 2;
        if (tab->isCloseable())
        {
            tabsWidth += closeWidth;
        }
    }

    if (m_collapsible)
    {
        tabsWidth += TAB_SIZE;
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

    Size tabSize = getTabSize();
    Rect tabsRect = getTabsRect();

    int x = tabsRect.x;
    int y = tabsRect.y;
    if (m_collapsible)
    {
        if (isHorizontal())
        {
            x += TAB_SIZE;
        }
        else
        {
            y += TAB_SIZE;
        }
    }

    for (Tab* tab : m_tabs)
    {
        tab->setPosition(x, y);
        tab->setSize(tabSize);

        if (isHorizontal())
        {
            x += tabSize.width;
        }
        else
        {
            y += tabSize.height;
        }
    }

    if (!m_collapsible || !m_collapsed)
    {
        Widget* activeWidget = getActiveTab();

        if (activeWidget != NULL)
        {
            Rect contentRect = getContentRect();

            activeWidget->setSize(Size(contentRect.width, contentRect.height));
            activeWidget->setPosition(contentRect.x, contentRect.y);
            activeWidget->layout();
        }
    }
}

bool Tabs::draw(Surface* surface)
{
    Rect tabsRect = getTabsRect();

#if 0
    log(DEBUG, "draw: m_setSize: width=%d, height=%d", m_setSize.width, m_setSize.height);

    log(DEBUG, "draw: tabsRect: x=%d, y=%d, width=%d, height=%d", tabsRect.x, tabsRect.y, tabsRect.width, tabsRect.height);
#endif

    if (!m_tabs.empty() && m_activeTab == NULL)
    {
        log(ERROR, "draw: Invalid active tab: %d", m_activeTab);
        m_activeTab = (m_tabs.back());
    }

    if (m_collapsible)
    {
        Icon* icon;
        if (m_collapsed)
        {
            icon = m_closedIcon;
        }
        else
        {
            icon = m_openIcon;
        }

        Size iconSize = icon->getSize();
        int iconX = (TAB_SIZE / 2) - (iconSize.width / 2);
        int iconY = (TAB_SIZE / 2) - (iconSize.height / 2);

        icon->draw(
            surface, 
            tabsRect.x + iconX,
            tabsRect.y + iconY);
    }

    unsigned int tabIdx;
    vector<Tab*>::iterator it;
    for (it = m_tabs.begin(), tabIdx = 0; it != m_tabs.end(); it++, tabIdx++)
    {
        Tab* tab = *it;
        SurfaceViewPort viewport(surface, tab->getX(), tab->getY(), tab->getWidth(), tab->getHeight());
        tab->draw(&viewport);
    }

    if (!m_tabs.empty() && (!m_collapsible || !m_collapsed))
    {
        Widget* activeWidget = m_activeTab->getContent();
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
 
            if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON && m_collapsible)
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

            for (Tab* tab : m_tabs)
            {
                if (tab->intersects(mouseEvent->x, mouseEvent->y))
                {
                    if (mouseButtonEvent->direction)
                    {
                        m_collapsed = false;
                    }
                    return tab->handleEvent(event);
                }
            }

            return this;
        }
        else if (!m_tabs.empty() && m_activeTab != NULL)
        {
            Widget* activeWidget = m_activeTab->getContent();

            if (activeWidget != NULL)
            {
                return activeWidget->handleEvent(event);
            }
        }
        return this;
    }

    return NULL;
}

vector<Widget*> Tabs::getChildren()
{
    vector<Widget*> children;

    if (m_activeTab)
    {
        children.push_back(m_activeTab->getContent());
    }

    return children;
}

void Tabs::addTab(std::wstring title, Widget* content, bool closeable)
{
    addTab(title, NULL, content, closeable);
}

void Tabs::addTab(std::wstring title, Icon* icon, Widget* content, bool closeable)
{
    Tab* tab = new Tab(this, title, icon, content, closeable);

     addTab(tab, m_tabs.end());
}

void Tabs::addTab(Tab* tab, vector<Tab*>::iterator pos)
{
    tab->setParent(this);
    tab->incRefCount();
    tab->dragCancelledSignal().clear();
    tab->dragCancelledSignal().connect(sigc::mem_fun(*this, &Tabs::onDragCancelled));
    m_tabs.insert(pos, tab);

    if (m_activeTab == NULL)
    {
        m_activeTab = tab;
    }

    setDirty();
}


void Tabs::closeTab(Widget* widget, bool emitChangeSignal)
{
    vector<Tab*>::iterator it;

    unsigned int i;
    for (i = 0, it = m_tabs.begin(); it != m_tabs.end(); it++, i++)
    {
        Tab* tab = *it;
        if (tab->getContent() == widget)
        {
            bool isActive = (tab == m_activeTab);

            tab->decRefCount();
            m_tabs.erase(it);

            if (isActive)
            {
                if (m_tabs.empty())
                {
                    m_activeTab = NULL;
                }
                else
                {
                    if (m_tabs.size() >= i)
                    {
                        i = m_tabs.size() - 1;
                    }
                    m_activeTab = m_tabs[i];
                }
            }

            if (isActive && emitChangeSignal)
            {
                m_changeTabSignal.emit(m_activeTab->getContent());
            }

            layout();
            setDirty();
            return;
        }
    }
}

void Tabs::closeActiveTab(MenuItem* item)
{
    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        closeTab(activeWidget);
    }
}

void Tabs::closeAllTabs(MenuItem* item)
{
    vector<Tab*> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab* tab : tabs)
    {
        if (tab->isCloseable())
        {
            closeTab(tab->getContent(), false);
        }
    }
}

void Tabs::closeAllButActiveTab(MenuItem* item)
{
    Widget* activeWidget = getActiveTab();

    vector<Tab*> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab* tab : tabs)
    {
        if (tab->isCloseable() && tab->getContent() != activeWidget)
        {
            closeTab(tab->getContent(), false);
        }
    }
}

void Tabs::setActiveTab(Tab* tab)
{
    m_activeTab = tab;

    m_changeTabSignal.emit(m_activeTab->getContent());

    setDirty();
}


void Tabs::setActiveTab(Widget* tabContent)
{
    int i = 0;
    for (Tab* tab : m_tabs)
    {
        if (tab->getContent() == tabContent)
        {
            m_activeTab = tab;

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
    for (Tab* tab : m_tabs)
    {
        if (tab->getContent() == tabContent)
        {
            return i;
        }
        i++;
    }

    // Not found
    return -1;
}

void Tabs::nextTab()
{
    int idx = getTabIndex(m_activeTab);
    if (idx == -1)
    {
        return;
    }

    idx++;

    if ((unsigned int)idx >= m_tabs.size())
    {
        idx = 0;
    }

    m_activeTab = m_tabs[idx];

    setDirty();
}

void Tabs::prevTab()
{
    int idx = getTabIndex(m_activeTab);
    if (idx == -1)
    {
        return;
    }

    idx--;

    if (idx < 0)
    {
        idx = m_tabs.size() - 1;
    }
    m_activeTab = m_tabs[idx];

    setDirty();
}

int Tabs::getTabIndex(Tab* tab)
{
    unsigned int i;
    for (i = 0; i < m_tabs.size(); i++)
    {
        if (m_tabs[i] == tab)
        {
            return i;
        }
    }
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

    for (Tab* tab : m_tabs)
    {
        tab->dump(level + 1);
    }

    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        activeWidget->dump(level + 1);
    }
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

bool Tabs::onDragDrop(Widget* widget, Vector2D pos)
{
    log(DEBUG, "onDragDrop: Dropped widget: %ls", widget->getWidgetName().c_str());

    if (typeid(*widget) == typeid(Tab))
    {
        Tab* droppedTab = (Tab*)widget;

        vector<Tab*>::iterator it;
        for (it = m_tabs.begin(); it != m_tabs.end(); it++)
        {
            if ((*it)->getX() > pos.x)
            {
                break;
            }
        }

        addTab(droppedTab, it);

        return true;
    }

    return false;
}

bool Tabs::onDragCancelled(Widget* widget)
{
    
    log(DEBUG, "onDragCancelled: widget: %ls", widget->getWidgetName().c_str());

    if (typeid(*widget) == typeid(Tab))
    {
        Tab* tab = (Tab*)widget;
        addTab(tab, m_tabs.end());
    }
    return true;
}

