#ifndef __FRONTIER_WIDGETS_TABS_H_
#define __FRONTIER_WIDGETS_TABS_H_

#include <frontier/widgets.h>

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

class Tab : public Widget
{
 protected:
    Tabs* m_tabs;

    std::wstring m_title;
    Icon* m_icon;
    Widget* m_content;
    bool m_closeable;

    bool m_mouseDown;
    Geek::Vector2D m_mouseDownPos;

 public:
    Tab(Tabs* tabs, std::wstring title, Icon* icon, Widget* content, bool closeable);
    Tab(FrontierApp* app, std::wstring title, Icon* icon, Widget* content, bool closeable);
    virtual ~Tab();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void setTabs(Tabs* tabs) { m_tabs = tabs; }

    void setTitle(std::wstring title);
    std::wstring getTitle() { return m_title; }
    Icon* getIcon() { return m_icon; }
    Widget* getContent() { return m_content; }
    bool isCloseable() { return m_closeable; }
};

class Tabs : public Widget
{
 protected:
    Tab* m_activeTab;
    std::vector<Tab*> m_tabs;

    TabPlacement m_placement;
    bool m_collapsible;
    bool m_collapsed;
    bool m_addButton;
    Icon* m_openIcon;
    Icon* m_closedIcon;
    Icon* m_dropDownIcon;
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
    Tabs(FrontierApp* app);
    Tabs(FrontierWindow* app);
    Tabs(FrontierApp* app, bool collapsible, TabPlacement placement);
    Tabs(FrontierWindow* window, bool collapsible, TabPlacement placement);
    Tabs(FrontierApp* app, bool collapsible, bool addButton, TabPlacement placement);
    Tabs(FrontierWindow* window, bool collapsible, bool addButton, TabPlacement placement);
    virtual ~Tabs();

    virtual void init();

    virtual void calculateSize();
    virtual void layout();
    virtual void clearDirty();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void setCollapsible(bool collapsible);
    bool isCollapsible() { return m_collapsible; }
    void setTabPlacement(TabPlacement tabPlacement);
    TabPlacement getTabPlacement() { return m_placement; }
    bool isHorizontal() { return (m_placement == TAB_TOP || m_placement == TAB_BOTTOM); }

    virtual std::vector<Widget*> getChildren();

    void addTab(std::wstring title, Widget* content, bool closeable = false);
    void addTab(std::wstring title, Icon* icon, Widget* content, bool closeable = false);
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

    virtual void dump(int level);

    virtual sigc::signal<void, Widget*> changeTabSignal() { return m_changeTabSignal; }
    virtual sigc::signal<void, Widget*> closeTabSignal() { return m_closeTabSignal; }
    virtual sigc::signal<void> addClickSignal() { return m_addTabSignal; }
};

};

#endif
