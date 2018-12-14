#ifndef __FRONTIER_WIDGETS_LIST_H_
#define __FRONTIER_WIDGETS_LIST_H_

#include <frontier/widgets.h>
#include <frontier/fontawesome.h>

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

    virtual Widget* handleMessage(Frontier::Message* msg);

    virtual sigc::signal<void, ListItem*> clickSignal() { return m_clickSignal; }
    virtual sigc::signal<void, ListItem*> doubleClickSignal() { return m_doubleClickSignal; }
};

class TextListItem : public ListItem
{
 private:
    uint32_t m_icon;
    std::wstring m_text;

 public:
    TextListItem(FrontierApp* ui, std::wstring text);
    TextListItem(FrontierApp* ui, uint32_t icon, std::wstring text);
    TextListItem(FrontierWindow* ui, std::wstring text);
    TextListItem(FrontierWindow* ui, uint32_t icon, std::wstring text);
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

 public:
    TreeListItem(FrontierApp* ui, std::wstring text);
    TreeListItem(FrontierApp* ui, uint32_t icon, std::wstring text);
    TreeListItem(FrontierWindow* ui, std::wstring text);
    TreeListItem(FrontierWindow* ui, uint32_t icon, std::wstring text);
    virtual ~TreeListItem();

    void addItem(ListItem* item);

    void setOpen(bool open);

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Frontier::Message* msg);
};

class List : public Widget
{
 private:
    std::vector<ListItem*> m_list;
    ListItem* m_selected;

    sigc::signal<void, ListItem*> m_selectSignal;

 public:
    List(FrontierApp* ui);
    List(FrontierWindow* window);
    virtual ~List();

    virtual void calculateSize();
    virtual void layout();
    virtual bool draw(Geek::Gfx::Surface* surface, Rect visible);

    virtual Widget* handleMessage(Frontier::Message* msg);

    void clearItems(bool setDirty = true);
    void addItem(ListItem* item);
    void setSelected(ListItem* item);
    void clearSelected(ListItem* item);
    ListItem* getSelected() { return m_selected; }
    ListItem* getItem(int i) { return m_list.at(i); }

    virtual sigc::signal<void, ListItem*> selectSignal() { return m_selectSignal; }
};

class MenuList : public List
{
 private:
    std::vector<MenuItem*> m_menuItems;

 public:
    MenuList(FrontierApp* ui, Menu* menu);
    MenuList(FrontierWindow* window, Menu* menu);
    MenuList(FrontierApp* ui, std::vector<MenuItem*> menu);
    MenuList(FrontierWindow* window, std::vector<MenuItem*> menu);
    virtual ~MenuList();

    virtual void init();

    void setMenu(std::vector<MenuItem*> menuItems);
};

};

#endif
