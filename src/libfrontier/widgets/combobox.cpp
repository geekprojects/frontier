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


#include <frontier/widgets/combobox.h>
#include <frontier/widgets/label.h>
#include <typeinfo>

using namespace std;
using namespace Geek;
using namespace Frontier;

FRONTIER_WIDGET(ComboBox, Frontier::ComboBox)

ComboBox::ComboBox(FrontierApp* ui) : Frame(ui, true)
{
    initComboBox();
}

ComboBox::ComboBox(FrontierWindow* ui) : Frame(ui, true)
{
    initComboBox();
}

ComboBox::ComboBox(FrontierApp* ui, vector<wstring> options) : Frame(ui, true)
{
    initComboBox();

    for (wstring option : options)
    {
        addOption(option);
    }
    updateOptions();
}

ComboBox::ComboBox(FrontierWindow* ui, vector<wstring> options) : Frame(ui, true)
{
    initComboBox();

    for (wstring option : options)
    {
        addOption(option);
    }
    updateOptions();
}

ComboBox::~ComboBox()
{
    clearOptions();
}

void ComboBox::initComboBox()
{
    m_textInput = new TextInput(m_app, L"");
    m_button = new IconButton(m_app, m_app->getTheme()->getIcon(FRONTIER_ICON_ARROW_DOWN));

    m_button->clickSignal().connect(sigc::mem_fun(*this, &ComboBox::openDropDown));

    add(m_textInput);
    add(m_button);

    m_comboBoxDropDown = new ComboBoxDropDown(m_app);
    m_comboBoxDropDown->getList()->selectSignal().connect(sigc::mem_fun(*this, &ComboBox::optionSelected));

    updateOptions();
}

void ComboBox::addOption(wstring text)
{
    addOption(text, NULL);
}

void ComboBox::addOption(wstring text, void* data)
{
    ListItem* item = new TextListItem(m_comboBoxDropDown, text);
    item->setPrivateData(data);
    item->incRefCount();
    m_options.push_back(item);
}

void ComboBox::clearOptions()
{
    //m_comboBoxDropDown->getList()->clearItems();

    for (ListItem* option : m_options)
    {
        option->decRefCount();
    }
    m_options.clear();
}

void ComboBox::updateOptions()
{
    ListItem* selected = m_comboBoxDropDown->getList()->getSelected();
    m_comboBoxDropDown->getList()->clearItems();

    for (ListItem* option : m_options)
    {
        m_comboBoxDropDown->getList()->addItem(option);
    }

    if (selected != NULL)
    {
        m_comboBoxDropDown->getList()->setSelected(selected);
    }
}

void ComboBox::selectOption(ListItem* option)
{
    if (typeid(*option) == typeid(TextListItem))
    {
        TextListItem* tli = (TextListItem*)option;
        m_textInput->setText(tli->getText());
    }
    else
    {
        log(WARN, "selectOption: selected item is not a TextListItem");
    }

    option->setSelected();
}

void ComboBox::selectOption(std::wstring text)
{
    for (ListItem* option : m_options)
    {
        if (typeid(*option) == typeid(TextListItem))
        {
            TextListItem* tli = (TextListItem*)option;
            if (tli->getText() == text)
            {
                selectOption(option);
                break;
            }
        }
    }
}

void ComboBox::selectOption(void* data)
{
    for (ListItem* option : m_options)
    {
        if (option->getPrivateData() == data)
        {
            selectOption(option);
            break;
        }
    }
}

ListItem* ComboBox::getSelectedOption()
{
    return m_comboBoxDropDown->getList()->getSelected();
}

void ComboBox::openDropDown(Widget* button)
{
    Vector2D widgetPos = getAbsolutePosition();
    widgetPos.y += m_textInput->getHeight();

    Vector2D screenPos = getWindow()->getScreenPosition(widgetPos);

    m_comboBoxDropDown->show();
    m_comboBoxDropDown->setPosition(screenPos);
    m_comboBoxDropDown->setSize(Size(m_textInput->getWidth(), 20));
}

void ComboBox::optionSelected(ListItem* option)
{
    log(DEBUG, "optionSelected: Here!");
    if (option != NULL)
    {
        selectOption(option);
    }
    m_comboBoxDropDown->hide();

    m_selectSignal.emit(option);
}

ComboBoxDropDown::ComboBoxDropDown(FrontierApp* app) : FrontierWindow(app, L"", WINDOW_TOOL_TIP)
{
    setSize(Size(20, 20));

    Frame* frame = new Frame(this, false);
    m_list = new List(this);
    frame->add(m_list);
    setContent(frame);
}

ComboBoxDropDown::~ComboBoxDropDown()
{
}

bool ComboBoxDropDown::init()
{
    return true;
}

void ComboBoxDropDown::lostFocus()
{
    log(DEBUG, "lostFocus: Closing!");
    hide();
}



