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
#include <frontier/widgets/iconbutton.h>
#include <frontier/fontawesome.h>

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define TABS_WIDGET_NAME L"Tabs"

Tabs::Tabs(FrontierApp* ui) : Widget(ui, TABS_WIDGET_NAME)
{
    setup(false, false, TAB_TOP);
}

Tabs::Tabs(FrontierWindow* window) : Widget(window, TABS_WIDGET_NAME)
{
    setup(false, false, TAB_TOP);
}

Tabs::Tabs(FrontierApp* ui, bool collapsible, TabPlacement placement) : Widget(ui, TABS_WIDGET_NAME)
{
    setup(collapsible, false, placement);
}

Tabs::Tabs(FrontierWindow* window, bool collapsible, TabPlacement placement) : Widget(window, TABS_WIDGET_NAME)
{
    setup(collapsible, false, placement);
}

Tabs::Tabs(FrontierApp* ui, bool collapsible, bool addButton, TabPlacement placement) : Widget(ui, TABS_WIDGET_NAME)
{
    setup(collapsible, addButton, placement);
}

Tabs::Tabs(FrontierWindow* window, bool collapsible, bool addButton, TabPlacement placement) : Widget(window, TABS_WIDGET_NAME)
{
    setup(collapsible, addButton, placement);
}

void Tabs::setup(bool collapsible, bool addButton, TabPlacement placement)
{
    m_collapsible = collapsible;
    m_collapsed = false;
    m_addButton = addButton;
    m_placement = placement;

    m_activeTab = NULL;
    m_addButtonWidget = NULL;
    m_collapseButtonWidget = NULL;
}

Tabs::~Tabs()
{
    for (Tab* tab : m_tabs)
    {
        tab->decRefCount();
    }
    m_tabs.clear();

    if (m_addButtonWidget != NULL)
    {
        m_addButtonWidget->decRefCount();
    }
    if (m_collapseButtonWidget != NULL)
    {
        m_collapseButtonWidget->decRefCount();
    }
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

    if (m_addButton)
    {
        m_addButtonWidget = new IconButton(m_app, m_app->getTheme()->getIcon(FRONTIER_ICON_PLUS));
        m_addButtonWidget->incRefCount();
        m_addButtonWidget->setParent(this);
        m_addButtonWidget->setDirty();
        m_addButtonWidget->clickSignal().connect(sigc::mem_fun(*this, &Tabs::onAddTab));
    }

    if (m_collapsible)
    {
        m_collapseButtonWidget = new IconButton(m_app, m_closedIcon);
        m_collapseButtonWidget->incRefCount();
        m_collapseButtonWidget->setParent(this);
        m_collapseButtonWidget->setDirty();
        //m_collapseButtonWidget->clickSignal().connect(sigc::mem_fun(*this, &Tabs::onCollapseTabs));
    }

    dragDropSignal().connect(sigc::mem_fun(*this, &Tabs::onDragDrop));
}

void Tabs::calculateSize()
{
    if (m_addButton)
    {
        m_addButtonWidget->calculateSize();
    }
    if (m_collapsible)
    {
        m_collapseButtonWidget->calculateSize();
    }

    m_tabsSize.set(0, 0);
    for (Tab* tab : m_tabs)
    {
        tab->calculateSize();
        Size tabMin = tab->getMinSize();

        if (isHorizontal())
        {
            if (m_tabsSize.height < tabMin.height)
            {
                m_tabsSize.height = tabMin.height;
            }
            m_tabsSize.width += tabMin.width;
        }
        else
        {
            if (m_tabsSize.width < tabMin.width)
            {
                m_tabsSize.width = tabMin.width;
            }
            m_tabsSize.height += tabMin.height;
        }
    }
    m_tabsSize.width++;
    m_tabsSize.height++;

    BoxModel boxModel = getBoxModel();
    m_minSize.width = boxModel.getWidth();
    m_minSize.height = boxModel.getHeight();
    m_minSize += m_tabsSize;

    if (isHorizontal())
    {
        m_maxSize.set(WIDGET_SIZE_UNLIMITED, m_tabsSize.height);
        if (m_addButton)
        {
            m_minSize.width += m_addButtonWidget->getMinSize().width;
        }
        if (m_collapsible)
        {
            m_minSize.width += m_collapseButtonWidget->getMinSize().width;
        }
    }
    else
    {
        m_maxSize.set(m_tabsSize.width, WIDGET_SIZE_UNLIMITED);
        if (m_addButton)
        {
            m_minSize.height += m_addButtonWidget->getMinSize().height;
        }
        if (m_collapsible)
        {
            m_minSize.height += m_collapseButtonWidget->getMinSize().height;
        }
    }

    if (m_tabs.empty() || (m_collapsible && m_collapsed))
    {
        return;
    }

    m_maxSize = m_minSize;

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
            activeMaxSize.width = WIDGET_SIZE_UNLIMITED;
        }
        else
        {
            activeMaxSize.height = WIDGET_SIZE_UNLIMITED;
        }
    }

    m_minSize += activeMinSize;
    m_maxSize += activeMaxSize;

    if (getStyle("expand-horizontal") == 1)
    {
        m_maxSize.width = WIDGET_SIZE_UNLIMITED;
    }
    if (getStyle("expand-vertical") == 1)
    {
        m_maxSize.height = WIDGET_SIZE_UNLIMITED;
    }
}

void Tabs::layout()
{
    Rect tabsRect = getTabsRect();
    if (m_addButton)
    {
        Vector2D pos;
        if (isHorizontal())
        {
            pos.x = (tabsRect.x + tabsRect.width) - m_addButtonWidget->getMinSize().width;
            pos.y = tabsRect.y;
        }
        else
        {
            pos.x = tabsRect.x;
            pos.y = (tabsRect.y + tabsRect.height) - m_addButtonWidget->getMinSize().height;
        }
        m_addButtonWidget->setPosition(pos.x, pos.y);
        m_addButtonWidget->setSize(m_addButtonWidget->getMinSize());
    }

    if (m_tabs.empty())
    {
        return;
    }

    int tabSize;
    if (isHorizontal())
    {
        tabSize = tabsRect.height;
    }
    else
    {
        tabSize = tabsRect.width;
    }

    int x = tabsRect.x;
    int y = tabsRect.y;
    if (m_collapsible)
    {
        m_collapseButtonWidget->setPosition(x, y);
        m_collapseButtonWidget->setSize(m_collapseButtonWidget->getMinSize());

        if (isHorizontal())
        {
            x += tabSize;
        }
        else
        {
            y += tabSize;
        }
    }

    Size idealTabSize = getTabSize();
    for (Tab* tab : m_tabs)
    {
        Size tabSize = tab->getMinSize();
        tab->setPosition(x, y);

        if (isHorizontal())
        {
            if (tabSize.width < idealTabSize.width)
            {
                tabSize.width = idealTabSize.width;
            }
            x += tabSize.width;
        }
        else
        {
            if (tabSize.height < idealTabSize.height)
            {
                tabSize.height = idealTabSize.height;
            }
            y += tabSize.height;
        }
        tab->setSize(tabSize);
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

void Tabs::clearDirty()
{
    m_dirty = 0;
    for (Tab* tab : m_tabs)
    {
        tab->clearDirty();
    }

    if (m_activeTab != NULL)
    {
        m_activeTab->clearDirty();
    }
}

bool Tabs::draw(Surface* surface)
{
    bool dirtySize = isDirty(DIRTY_SIZE);
    if (dirtySize)
    {
        drawBorder(surface);
    }

    if (!m_tabs.empty() && m_activeTab == NULL)
    {
        log(ERROR, "draw: Invalid active tab: %d", m_activeTab);
        m_activeTab = (m_tabs.back());
    }

    if (m_collapsible)
    {
        SurfaceViewPort viewport(
            surface,
            m_collapseButtonWidget->getX(),
            m_collapseButtonWidget->getY(),
            m_collapseButtonWidget->getWidth(),
            m_collapseButtonWidget->getHeight());
        m_collapseButtonWidget->draw(&viewport);
    }

    for (Tab* tab : m_tabs)
    {
        if (dirtySize || tab->isDirty())
        {
            SurfaceViewPort viewport(surface, tab->getX(), tab->getY(), tab->getWidth(), tab->getHeight());
            tab->draw(&viewport);
        }
    }

    if (m_addButton)
    {
        SurfaceViewPort viewport(
            surface,
            m_addButtonWidget->getX(),
            m_addButtonWidget->getY(),
            m_addButtonWidget->getWidth(),
            m_addButtonWidget->getHeight());
        m_addButtonWidget->draw(&viewport);
    }

    if (!m_tabs.empty() && (!m_collapsible || !m_collapsed))
    {
        Widget* activeWidget = m_activeTab->getContent();
        if (activeWidget != NULL && (dirtySize || activeWidget->isDirty() || activeWidget->hasChildren()))
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
            x -= tabsRect.x;
            y -= tabsRect.y;

            if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON)
            {
                MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;

                if (m_collapsible)
                {
                    if (m_collapseButtonWidget->intersects(mouseEvent->x, mouseEvent->y))
                    {
                        if (mouseButtonEvent->direction)
                        {
                            m_collapsed = !m_collapsed;
                            setDirty();
                        }
                        if (m_collapsed)
                        {
                            m_collapseButtonWidget->setIcon(m_openIcon);
                        }
                        else
                        {
                            m_collapseButtonWidget->setIcon(m_closedIcon);
                        }

                        return m_collapseButtonWidget->handleEvent(event);
                    }
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
            }
            else if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
            {
                for (Tab* tab : m_tabs)
                {
                    if (tab->intersects(mouseEvent->x, mouseEvent->y))
                    {
                        return tab->handleEvent(event);
                    }
                }
            }

            if (m_addButtonWidget != NULL && m_addButtonWidget->intersects(mouseEvent->x, mouseEvent->y))
            {
                return m_addButtonWidget->handleEvent(event);
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

    if (m_activeTab != NULL)
    {
        children.push_back(m_activeTab->getContent());
    }

    for (Tab* tab : m_tabs)
    {
        children.push_back(tab);
    }

    return children;
}

Tab* Tabs::addTab(std::wstring title, Widget* content, bool closeable)
{
    return addTab(title, NULL, content, closeable);
}

Tab* Tabs::addTab(std::wstring title, Icon* icon, Widget* content, bool closeable)
{
    Tab* tab = new Tab(this, title, icon, content, closeable);

    addTab(tab, m_tabs.end());

    return tab;
}

void Tabs::addTab(Tab* tab, vector<Tab*>::iterator pos)
{
    tab->setParent(this);
    tab->incRefCount();
    tab->dragCancelledSignal().clear();
    tab->dragCancelledSignal().connect(sigc::mem_fun(*this, &Tabs::onDragCancelled));
    m_tabs.insert(pos, tab);

    switch (m_placement)
    {
        case TAB_TOP:
            tab->setWidgetClass(L"tabTop");
            break;
        case TAB_RIGHT:
            tab->setWidgetClass(L"tabRight");
            break;
        case TAB_BOTTOM:
            tab->setWidgetClass(L"tabBottom");
            break;
        case TAB_LEFT:
            tab->setWidgetClass(L"tabLeft");
            break;
    }

    if (m_activeTab == NULL)
    {
        setActiveTab(tab);
    }

    setDirty();
}


void Tabs::closeTab(Widget* widget, bool emitChangeSignal)
{
    vector<Tab*>::iterator it;

    unsigned int i;
    for (i = 0, it = m_tabs.begin(); it != m_tabs.end(); ++it, i++)
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
    if (m_activeTab != NULL)
    {
        m_activeTab->clearSelected();
    }

    m_activeTab = tab;
    m_activeTab->setSelected();
    m_activeTab->setDirty(DIRTY_ALL, true);

    setDirty(DIRTY_ALL, false);

    m_changeTabSignal.emit(m_activeTab->getContent());
}


void Tabs::setActiveTab(Widget* tabContent)
{
    if (m_activeTab != NULL)
    {
        m_activeTab->clearSelected();
    }

    int i = 0;
    for (Tab* tab : m_tabs)
    {
        if (tab->getContent() == tabContent)
        {
            m_activeTab = tab;
            m_activeTab->setSelected();
            m_activeTab->setDirty(DIRTY_ALL, true);

            setDirty();
            return;
        }
        i++;
    }

    return;
}

Tab* Tabs::getTab(Widget* tabContent)
{
    for (Tab* tab : m_tabs)
    {
        if (tab->getContent() == tabContent)
        {
            return tab;
        }
    }
    return NULL;
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

bool Tabs::isVisible(Widget* child)
{
    bool visible = Widget::isVisible();
    if (child == NULL || !visible)
    {
        return visible;
    }

    if (m_collapsed)
    {
        return false;
    }

    return (child == getActiveTab());
}

void Tabs::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }
    log(DEBUG, "%sTabs(%p): x=%d, y=%d, size=%s", spaces.c_str(), this, m_position.x, m_position.y, m_setSize.toString().c_str());

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
        major -= 25;
    }

    if (m_addButton)
    {
        major -= 25;
    }

    int tabMajor = major / m_tabs.size();

    int maxTabSize = m_tabs.at(0)->getStyle("max-width");
    if (tabMajor > maxTabSize)
    {
        tabMajor = maxTabSize;
    }

    Size size;
    if (isHorizontal())
    {
        size.width = tabMajor;
        size.height = m_tabsSize.height;
    }
    else
    {
        size.width = m_tabsSize.width;
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
        r.height = m_tabsSize.height;
    }
    else
    {
        r.width = m_tabsSize.width;
        r.height = m_setSize.height;
    }

    switch (m_placement)
    {
        case TAB_TOP:
            break;

        case TAB_BOTTOM:
            r.y = m_setSize.height - m_tabsSize.height;
            break;

        case TAB_LEFT:
            break;

        case TAB_RIGHT:
            r.x = m_setSize.width - m_tabsSize.width;
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
        r.height = m_setSize.height - m_tabsSize.height;
    }
    else
    {
        r.width = m_setSize.width - m_tabsSize.width;
        r.height = m_setSize.height;
    }

    switch (m_placement)
    {
        case TAB_TOP:
	    r.y = m_tabsSize.height;
            break;

        case TAB_BOTTOM:
            break;

        case TAB_LEFT:
	    r.x = m_tabsSize.width;
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

void Tabs::onAddTab(Widget* button)
{
    m_addTabSignal.emit();
}

