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

#ifndef __FRONTIER_WIDGETS_COMBOBOX_H_
#define __FRONTIER_WIDGETS_COMBOBOX_H_

#include <frontier/window.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/list.h>

namespace Frontier
{

class ComboBoxDropDown;

/**
 * \brief Combo box which consists of a text input and a drop down to select from a list of options.
 *
 * \ingroup widgets
 */
class ComboBox : public Frame
{
 protected:
    TextInput* m_textInput;
    IconButton* m_button;

    ComboBoxDropDown* m_comboBoxDropDown;

    std::vector<ListItem*> m_options;

    sigc::signal<void, ListItem*> m_selectSignal;

    void initComboBox();

    void openDropDown(Widget* button);
    void optionSelected(ListItem* option);

 public:
    ComboBox(FrontierApp* ui);
    ComboBox(FrontierWindow* ui);
    ComboBox(FrontierApp* ui, std::vector<std::wstring> options);
    ComboBox(FrontierWindow* ui, std::vector<std::wstring> options);
    virtual ~ComboBox();

    void addOption(std::wstring text);
    void addOption(std::wstring text, void* data);
    std::vector<ListItem*>& getOptions() { return m_options; }
    void clearOptions();
    void updateOptions();

    void selectOption(ListItem* item);
    void selectOption(std::wstring text);
    void selectOption(void* data);
    ListItem* getSelectedOption();

    virtual sigc::signal<void, ListItem*> selectSignal() { return m_selectSignal; }
};

class ComboBoxDropDown : public FrontierWindow
{
 private:
    List* m_list;

 public:
    ComboBoxDropDown(FrontierApp* app);
    virtual ~ComboBoxDropDown();

    virtual bool init();

    void lostFocus();

    List* getList() { return m_list; }
};


};

#endif
