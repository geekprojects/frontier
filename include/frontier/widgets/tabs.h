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

#ifndef __FRONTIER_WIDGETS_TABS_H_
#define __FRONTIER_WIDGETS_TABS_H_

#include <frontier/widgets.h>

#define FRONTIER_PROP_TITLE L"title"

namespace Frontier
{

class Tabs;
class IconButton;
class Button;

enum TabPlacement
{
    TAB_TOP,
    TAB_BOTTOM,
    TAB_LEFT,
    TAB_RIGHT
};

/**
 * \brief A single Tab title representing a page within a Tabs Widget
 *
 * \ingroup widgets
 */
class Tab : public Widget
{
 protected:
    Icon* m_icon;
    bool m_closeable;

    bool m_mouseDown;
    Geek::Vector2D m_mouseDownPos;

 public:
    explicit Tab(FrontierApp* app);
    Tab(Tabs* tabs, std::wstring title, Icon* icon, Widget* content, bool closeable);
    Tab(FrontierApp* app, std::wstring title, Icon* icon, Widget* content, bool closeable);
    ~Tab() override;

    void calculateSize() override;
    void layout() override;

    bool draw(Geek::Gfx::Surface* surface) override;

    Widget* handleEvent(Frontier::Event* event) override;

    void setTitle(std::wstring title);
    std::wstring getTitle() { return getProperty(FRONTIER_PROP_TITLE).asString(); }
    void setIcon(Icon* icon);
    Icon* getIcon() { return m_icon; }
    bool isCloseable() const { return m_closeable; }

    Tabs* getTabs();

    void add(Widget* content) override;
    void setContent(Widget* content) { add(content); }
    Widget* getContent() { if (m_children.empty()) { return NULL; } else { return m_children.at(0); } }

    void setSelected() { m_selected = true; setDirty(DIRTY_STYLE); }
    void clearSelected() { m_selected = false; setDirty(DIRTY_STYLE); }
};

/**
 * \brief A Widget that allows access to multiple pages of child Widgets
 *
 * \ingroup widgets
 */
class Tabs : public Widget
{
 protected:
    Tab* m_activeTab;
    std::vector<Tab*> m_tabs;
    Size m_tabsSize;

    TabPlacement m_placement;
    bool m_collapsible;
    bool m_collapsed;
    bool m_addButton;
    Icon* m_openIcon;
    Icon* m_closedIcon;
    Frontier::IconButton* m_collapseButtonWidget;
    Frontier::IconButton* m_addButtonWidget;

    sigc::signal<void, Widget*> m_changeTabSignal;
    sigc::signal<void, Widget*> m_closeTabSignal;
    sigc::signal<void> m_addTabSignal;

    Frontier::Size getTabSize();
    Frontier::Rect getTabsRect();
    Frontier::Rect getContentRect();

    void setup(bool collapsible, bool addButton, TabPlacement placement);

    void addTab(Tab* tab, std::vector<Tab*>::iterator pos);
    int getTabIndex(Tab* tab);

    bool onDragDrop(Widget* widget, Geek::Vector2D pos);
    bool onDragCancelled(Widget* widget);
    void onAddTab(Widget* button);

 public:
    explicit Tabs(FrontierApp* app);
    Tabs(FrontierApp* app, bool collapsible, TabPlacement placement);
    Tabs(FrontierApp* app, bool collapsible, bool addButton, TabPlacement placement);
    ~Tabs() override;

    void init() override;

    void calculateSize() override;
    void layout() override;
    void clearDirty() override;

    bool draw(Geek::Gfx::Surface* surface) override;

    Widget* handleEvent(Frontier::Event* event) override;

    void setCollapsible(bool collapsible);
    bool isCollapsible() const { return m_collapsible; }
    void setTabPlacement(TabPlacement tabPlacement);
    TabPlacement getTabPlacement() { return m_placement; }
    bool isHorizontal() { return (m_placement == TAB_TOP || m_placement == TAB_BOTTOM); }

    std::vector<Widget*> getChildren() override;

    void add(Widget* content) override;
    Tab* addTab(std::wstring title, Widget* content, bool closeable = false);
    Tab* addTab(std::wstring title, Icon* icon, Widget* content, bool closeable = false);
    void closeTab(Widget* tab, bool emitChangeSignal = true);

    void closeActiveTab(MenuItem* item);
    void closeAllTabs(MenuItem* item);
    void closeAllButActiveTab(MenuItem* item);

    Widget* getActiveTab()
    {
        if (m_tabs.empty() || m_activeTab == NULL)
        {
            return NULL;
        }
        return m_activeTab->getContent();
    }

    void setActiveTab(Tab* tab);
    void setActiveTab(Widget* tabContent);
    int findTab(Widget* tabContent);
    Tab* getTab(Widget* tabContent);
    const std::vector<Tab*>& getTabs() { return m_tabs; }

    void nextTab();
    void prevTab();

    bool isVisible(Frontier::Widget* child) override;

    void dump(int level) override;

    virtual sigc::signal<void, Widget*> changeTabSignal() { return m_changeTabSignal; }
    virtual sigc::signal<void, Widget*> closeTabSignal() { return m_closeTabSignal; }
    virtual sigc::signal<void> addClickSignal() { return m_addTabSignal; }
};

};

#endif
