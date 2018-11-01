#ifndef __FRONTIER_WIDGETS_TABS_H_
#define __FRONTIER_WIDGETS_TABS_H_

#include <frontier/widgets.h>

namespace Frontier
{

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

    sigc::signal<void, Widget*> m_changeTabSignal;
    sigc::signal<void, Widget*> m_closeTabSignal;

    int getTabWidth();

 public:
    Tabs(FrontierApp* app);
    Tabs(FrontierWindow* app);
    virtual ~Tabs();

    virtual void calculateSize();
    virtual void layout();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void addTab(std::wstring title, Widget* content, bool closeable = false);
    void closeTab(Widget* tab);

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

    virtual void dump(int level);

    virtual sigc::signal<void, Widget*> changeTabSignal() { return m_changeTabSignal; }
    virtual sigc::signal<void, Widget*> closeTabSignal() { return m_closeTabSignal; }
};

};

#endif
