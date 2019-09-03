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
