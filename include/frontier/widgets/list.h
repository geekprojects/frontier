#ifndef __FRONTIER_WIDGETS_LIST_H_
#define __FRONTIER_WIDGETS_LIST_H_

#include <frontier/widgets.h>
#include <frontier/icon.h>

#include <geek/core-thread.h>

namespace Frontier
{

class List;
class Menu;

class ListItem : public Widget
{
 protected:
    List* m_list;
    bool m_selected;
    sigc::signal<void, ListItem*> m_clickSignal;
    sigc::signal<void, ListItem*> m_doubleClickSignal;

 public:
    ListItem(FrontierApp* ui);
    ListItem(FrontierWindow* ui);
    virtual ~ListItem();

    virtual void setList(List* list);
    virtual void clearSelected(bool updateList = true);
    virtual void setSelected(bool updateList = true);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual sigc::signal<void, ListItem*> clickSignal() { return m_clickSignal; }
    virtual sigc::signal<void, ListItem*> doubleClickSignal() { return m_doubleClickSignal; }
};

class TextListItem : public ListItem
{
 private:
    Icon* m_icon;
    std::wstring m_text;

 public:
    TextListItem(FrontierApp* ui, std::wstring text);
    TextListItem(FrontierApp* ui, Icon* icon, std::wstring text);
    TextListItem(FrontierWindow* ui, std::wstring text);
    TextListItem(FrontierWindow* ui, Icon* icon, std::wstring text);
    virtual ~TextListItem();

    void setText(std::wstring wtext);
    std::wstring getText() { return m_text; }

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

class TreeListItem : public TextListItem
{
 private:
    std::vector<ListItem*> m_items;
    int m_titleHeight;
    bool m_open;
    sigc::signal<void, ListItem*> m_expandSignal;

 public:
    TreeListItem(FrontierApp* ui, std::wstring text);
    TreeListItem(FrontierApp* ui, Icon* icon, std::wstring text);
    TreeListItem(FrontierWindow* ui, std::wstring text);
    TreeListItem(FrontierWindow* ui, Icon* icon, std::wstring text);
    virtual ~TreeListItem();

    void addItem(ListItem* item);

    void setOpen(bool open);

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    sigc::signal<void, ListItem*> expandSignal() { return m_expandSignal; }
};

class List : public Widget
{
 private:
    Geek::Mutex* m_listMutex;
    std::vector<ListItem*> m_list;
    ListItem* m_selected;
    bool m_horizontal;

    sigc::signal<void, ListItem*> m_selectSignal;
    sigc::signal<void, ListItem*, Geek::Vector2D> m_contextMenuSignal;

 public:
    List(FrontierApp* ui, bool horizontal = false);
    List(FrontierWindow* window, bool horizontal = false);
    virtual ~List();

    bool isHorizontal() { return m_horizontal; }

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface, Rect visible);

    virtual Widget* handleEvent(Frontier::Event* event);

    void clearItems(bool setDirty = true);
    void addItem(ListItem* item);
    void setSelected(ListItem* item);
    void clearSelected(ListItem* item);
    ListItem* getSelected() { return m_selected; }
    ListItem* getItem(int i) { return m_list.at(i); }

    virtual sigc::signal<void, ListItem*> selectSignal() { return m_selectSignal; }
    virtual sigc::signal<void, ListItem*, Geek::Vector2D> contextMenuSignal() { return m_contextMenuSignal; }
};

class MenuList : public List
{
 private:
    std::vector<MenuItem*> m_menuItems;

    void onSelect(ListItem* item);

 public:
    MenuList(FrontierApp* ui, Menu* menu, bool horizontal = false);
    MenuList(FrontierWindow* window, Menu* menu, bool horizontal = false);
    MenuList(FrontierApp* ui, std::vector<MenuItem*> menu, bool horizontal = false);
    MenuList(FrontierWindow* window, std::vector<MenuItem*> menu, bool horizontal = false);
    virtual ~MenuList();

    virtual void init();

    virtual void calculateSize();

    void setMenu(std::vector<MenuItem*> m_menu);
};

};

#endif
