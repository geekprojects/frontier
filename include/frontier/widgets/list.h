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

#ifndef __FRONTIER_WIDGETS_LIST_H_
#define __FRONTIER_WIDGETS_LIST_H_

#include <frontier/widgets.h>
#include <frontier/icon.h>

#include <geek/core-thread.h>

namespace Frontier
{

class List;
class Menu;

/**
 * \brief An item in a List Widget
 */
class ListItem : public Widget
{
 protected:
    List* m_list{};

 public:
    explicit ListItem(FrontierApp* ui);
    ~ListItem() override;

    virtual void setList(List* list);
    void clearSelected() { clearSelected(true); }
    virtual void clearSelected(bool updateList);
    void setSelected() { setSelected(true); }
    virtual void setSelected(bool updateList);

    Widget* handleEvent(Frontier::Event* event) override;
};

/**
 * \brief A List item that displays text
 */
class TextListItem : public ListItem
{
 private:
    Icon* m_icon;
    std::wstring m_text;

 public:
    TextListItem(FrontierApp* ui, std::wstring text);
    TextListItem(FrontierApp* ui, Icon* icon, std::wstring text);
    ~TextListItem() override;

    void setText(std::wstring wtext);
    std::wstring getText() { return m_text; }

    void calculateSize() override;
    bool draw(Geek::Gfx::Surface* surface) override;
};

/**
 * \brief A List item that allows nested ListItems to display a hierarchy
 */
class TreeListItem : public TextListItem
{
 private:
    int m_titleHeight;
    bool m_open;
    sigc::signal<void, ListItem*> m_expandSignal;

 public:
    TreeListItem(FrontierApp* ui, std::wstring text);
    TreeListItem(FrontierApp* ui, Icon* icon, std::wstring text);
    ~TreeListItem() override;

    void addItem(ListItem* item);

    void setOpen(bool open);

    void calculateSize() override;
    void layout() override;
    bool draw(Geek::Gfx::Surface* surface) override;

    Widget* handleEvent(Frontier::Event* event) override;

    sigc::signal<void, ListItem*> expandSignal() { return m_expandSignal; }
};

/**
 * \brief A widget that shows a List of child ListItems
 *
 * \ingroup widgets
 */
class List : public Widget
{
 private:
    Geek::Mutex* m_listMutex;
    ListItem* m_selected;
    bool m_horizontal;

    sigc::signal<void, ListItem*> m_selectSignal;
    sigc::signal<void, ListItem*, Geek::Vector2D> m_contextMenuSignal;

 public:
    explicit List(FrontierApp* ui);
    List(FrontierApp* ui, bool horizontal);
    ~List() override;

    bool isHorizontal() const { return m_horizontal; }

    void calculateSize() override;
    void layout() override;
    bool draw(Geek::Gfx::Surface* surface, Rect visible) override;

    Widget* handleEvent(Frontier::Event* event) override;

    void clearItems(bool setDirty = true);
    void addItem(ListItem* item);
    void setSelected(ListItem* item);
    void clearSelected(ListItem* item);
    ListItem* getSelected() { return m_selected; }
    ListItem* getItem(int i) { return (ListItem*)m_children.at(i); }

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
    MenuList(FrontierApp* ui, std::vector<MenuItem*> menu, bool horizontal = false);
    ~MenuList() override;

    void init() override;

    void calculateSize() override;

    void setMenu(std::vector<MenuItem*> m_menu);
};

}

#endif
