#ifndef __FRONTIER_WIDGETS_TABS_H_
#define __FRONTIER_WIDGETS_TABS_H_

#include <frontier/widgets.h>

namespace Frontier
{

enum TabPlacement
{
    TAB_TOP,
    TAB_BOTTOM,
    TAB_LEFT,
    TAB_RIGHT
};

struct Tab
{
    std::wstring title;
    Widget* content;
    bool closeable;
};

class Tabs : public Widget
{
 protected:
    unsigned int m_activeTab;
    std::vector<Tab> m_tabs;

    TabPlacement m_placement;
    bool m_collapsible;
    bool m_collapsed;

    sigc::signal<void, Widget*> m_changeTabSignal;
    sigc::signal<void, Widget*> m_closeTabSignal;

    Frontier::Size getTabSize();
    Frontier::Rect getTabsRect();
    Frontier::Rect getContentRect();
    bool isHorizontal() { return (m_placement == TAB_TOP || m_placement == TAB_BOTTOM); }

 public:
    Tabs(FrontierApp* app);
    Tabs(FrontierWindow* app);
    Tabs(FrontierApp* app, bool collapsible, TabPlacement placement);
    Tabs(FrontierWindow* window, bool collapsible, TabPlacement placement);
    virtual ~Tabs();

    virtual void init();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    void setCollapsible(bool collapsible);
    bool isCollapsible() { return m_collapsible; }
    void setTabPlacement(TabPlacement tabPlacement);
    TabPlacement getTabPlacement() { return m_placement; }

    void addTab(std::wstring title, Widget* content, bool closeable = false);
    void closeTab(Widget* tab, bool emitChangeSignal = true);

    void closeActiveTab(MenuItem* item);
    void closeAllTabs(MenuItem* item);
    void closeAllButActiveTab(MenuItem* item);

    Widget* getActiveTab()
    {
        if (m_tabs.empty())
        {
            return NULL;
        }
        if (m_activeTab >= m_tabs.size())
        {
            m_activeTab = m_tabs.size() - 1;
        }
        return m_tabs.at(m_activeTab).content;
    }

    void setActiveTab(Widget* tabContent);
    int findTab(Widget* tabContent);
    const std::vector<Tab>& getTabs() { return m_tabs; }

    virtual void dump(int level);

    virtual sigc::signal<void, Widget*> changeTabSignal() { return m_changeTabSignal; }
    virtual sigc::signal<void, Widget*> closeTabSignal() { return m_closeTabSignal; }
};

};

#endif
