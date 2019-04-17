/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
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


#include <frontier/frontier.h>

#include <frontier/widgets/button.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/label.h>
#include <frontier/widgets/list.h>
#include <frontier/widgets/resizeableframe.h>
#include <frontier/widgets/scrollbar.h>
#include <frontier/widgets/scroller.h>
#include <frontier/widgets/tabs.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/grid.h>
#include <frontier/widgets/combobox.h>
#include <frontier/widgets/terminal.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

class TooltipWindow;

class DemoApp : public FrontierApp
{
 private:
    FrontierWindow* m_mainWindow;
    Tabs* m_tabs;
    Button* m_textButton1;
    Button* m_textButton2;

    TooltipWindow* m_tooltipWindow;

    void onTextButton1();
    void onTextButton2();
    void onIconButton();

    void onCloseTab(Widget* tab);
    void onContextMenu(ListItem* item, Geek::Vector2D pos);
    void onMenuItem(MenuItem* item);

 public:
    DemoApp();
    ~DemoApp();

    virtual bool init();
};

using namespace Frontier;

class TooltipWindow : public FrontierWindow
{
 private:

 public:
    TooltipWindow(FrontierApp* app);
    virtual ~TooltipWindow();

    virtual bool init();
};

TooltipWindow::TooltipWindow(FrontierApp* app) : FrontierWindow(app, L"", WINDOW_TOOL_TIP)
{
    setSize(Size(20, 20));
}

TooltipWindow::~TooltipWindow()
{
}

bool TooltipWindow::init()
{
    setContent(new Label(this, L"Tool tip!"));
    return true;
}

DemoApp::DemoApp() : FrontierApp(L"Demo")
{
}

DemoApp::~DemoApp()
{
}

bool DemoApp::init()
{
    Menu* appMenu = new Menu();
    setAppMenu(appMenu);

    MenuItem* fileMenu = new MenuItem(L"File");
    appMenu->add(fileMenu);

    MenuItem* newItem = new MenuItem(L"New...");
    newItem->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onMenuItem));
    fileMenu->add(newItem);

    MenuItem* projectMenu = new MenuItem(L"Project");
    projectMenu->add(new MenuItem(L"New..."));
    projectMenu->add(new MenuItem(L"Open..."));
    projectMenu->add(new MenuItem(L"Save"));
    projectMenu->add(new MenuSeparator());
    projectMenu->add(new MenuItem(L"Something else..."));
    appMenu->add(projectMenu);

    MenuItem* editMenu = new MenuItem(L"Edit");
    editMenu->add(new MenuItem(L"Cut", L'x', 0));
    MenuItem* copyItem = new MenuItem(L"Copy", L'c', 0);
    copyItem->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onMenuItem));
    editMenu->add(copyItem);
    editMenu->add(new MenuItem(L"Paste", L'v', 0));
    editMenu->add(new MenuSeparator());
    editMenu->add(new MenuItem(L"Something different"));
    appMenu->add(editMenu);

    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    log(DEBUG, "init: Config Dir: %s", getConfigDir().c_str());

    ResizeableFrame* rootFrame = new ResizeableFrame(this, false);
    m_tabs = new Tabs(this, true, TAB_TOP);
    rootFrame->add(m_tabs);
    m_tabs->closeTabSignal().connect(sigc::mem_fun(*this, &DemoApp::onCloseTab));

    Frame* toolbarTab = new Frame(this, false);

    Frame* toolbar1 = new Frame(this, true);
    toolbar1->add(new IconButton(this, getTheme()->getIcon(FRONTIER_ICON_FOLDER_OPEN)));
    toolbar1->add(new IconButton(this, getTheme()->getIcon(FRONTIER_ICON_SAVE)));
    toolbar1->add(new IconButton(this, getTheme()->getIcon(FRONTIER_ICON_SYNC)));
    toolbarTab->add(toolbar1);
    m_tabs->addTab(L"Tool Bars", getTheme()->getIcon(FRONTIER_ICON_TOOLBOX), toolbarTab);

    /*
     * Labels
     */
    Frame* labelTab = new Frame(this, false);
    m_tabs->addTab(L"Labels", getTheme()->getIcon(FRONTIER_ICON_TAG), labelTab);

    Frame* labelFrame1 = new Frame(this, true);
    labelFrame1->add(new Label(this, L"Label:"));
    labelFrame1->add(new Label(this, L"I'm a label!"));
    labelTab->add(labelFrame1);

    Frame* labelFrame2 = new Frame(this, true);
    labelFrame2->add(new Label(this, L"Label:"));
    labelFrame2->add(new Label(this, L"I'm another label!"));
    labelTab->add(labelFrame2);

    {
        Frame* labelFrame3 = new Frame(this, true);
        labelFrame3->add(new Label(this, L"Left Align", ALIGN_LEFT));
        labelTab->add(labelFrame3);
    }

    {
        Frame* labelFrame4 = new Frame(this, true);
        labelFrame4->add(new Label(this, L"Center Align", ALIGN_CENTER));
        labelTab->add(labelFrame4);
    }

    {
        Frame* labelFrame5 = new Frame(this, true);
        labelFrame5->add(new Label(this, L"Right Align", ALIGN_RIGHT));
        labelTab->add(labelFrame5);
    }


    Frame* buttonTab = new Frame(this, false);
    Frame* buttonFrame1 = new Frame(this, true);
    buttonFrame1->add(new Label(this, L"Button:"));
    buttonFrame1->add(m_textButton1 = new Button(this, L"Click me!"));
    buttonFrame1->add(m_textButton2 = new Button(this, L"But not me!"));
    buttonTab->add(buttonFrame1);
    m_tabs->addTab(L"Buttons", buttonTab);

    Frame* iconButtonTab = new Frame(this, false);
    Frame* iconButtonFrame1 = new Frame(this, true);
    IconButton* iconButton;
    iconButtonFrame1->add(new Label(this, L"Icon Button:"));
    iconButtonFrame1->add(iconButton = new IconButton(this, getTheme()->getIcon(0xf0ae)));
    iconButtonTab->add(iconButtonFrame1);
    m_tabs->addTab(L"Icon Buttons", iconButtonTab);

    m_textButton1->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onTextButton1));
    m_textButton2->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onTextButton2));
    iconButton->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onIconButton));

    Frame* inputTab = new Frame(this, false);
    Frame* inputFrame1 = new Frame(this, true);
    TextInput* input1;
    inputFrame1->add(new Label(this, L"Default Text:"));
    inputFrame1->add(input1 = new TextInput(this, L"Default text"));
    inputTab->add(inputFrame1);
    Frame* inputFrame2 = new Frame(this, true);
    TextInput* input2;
    inputFrame2->add(new Label(this, L"Empty Text:"));
    inputFrame2->add(input2 = new TextInput(this));
    inputTab->add(inputFrame2);
    m_tabs->addTab(L"Inputs", inputTab);

    Frame* gridTab = new Frame(this, false);
    Grid* grid1 = new Grid(this);
    gridTab->add(grid1);
    grid1->put(0, 0, new Label(this, L"Small:"));
    grid1->put(1, 0, new Button(this, L"S"));
    grid1->put(0, 1, new Label(this, L"Very very large:"));
    grid1->put(1, 1, new TextInput(this, L"Input box"));
    grid1->put(0, 2, new Label(this, L"Very very very very very very large:"));
    //grid1->put(1, 2, new Button(this, L"LARGE BUTTON!!!"));
    grid1->put(2, 2, new Button(this, L"A LARGE BUTTON!!!"));
    m_tabs->addTab(L"Grid", gridTab);


    vector<wstring> options;
    options.push_back(L"Option 1");
    options.push_back(L"Option 2");
    options.push_back(L"Option 3");
    options.push_back(L"Option 4");
    options.push_back(L"Option 5");

    Frame* comboBoxTab = new Frame(this, false);
    Frame* comboBoxFrame1 = new Frame(this, true);
    ComboBox* comboBox1;
    comboBoxFrame1->add(new Label(this, L"Combo Box:"));
    comboBoxFrame1->add(comboBox1 = new ComboBox(this, options));
    comboBoxTab->add(comboBoxFrame1);
    m_tabs->addTab(L"ComboBox", comboBoxTab);

    Frame* terminalTab = new Frame(this, false);
    Terminal* terminal = new Terminal(this);
    //terminal->run("/usr/bin/top");
    //terminal->run("/bin/ls");

    vector<const char*> args;
    //args.push_back("/bin/ls -l");
    //terminal->run("/usr/local/bin/watch", args);
    //args.push_back("-l");
    //terminal->run("/bin/ls", args);
    //args.push_back("-l");
    terminal->run("/usr/local/bin/bash", args);
    terminalTab->add(terminal);

    m_tabs->addTab(L"Terminal", terminalTab);

    Frame* closeableTab = new Frame(this, false);
    m_tabs->addTab(L"Closeable", closeableTab, true);

    Frame* closeableFrame1 = new Frame(this, true);
    closeableFrame1->add(new Label(this, L"This tab is closeable!"));
    closeableTab->add(closeableFrame1);


    Frame* menuButtonTab = new Frame(this, false);

    Menu* menuListMenu = new Menu();
    MenuItem* menuListFileMenu = new MenuItem(L"File");
    menuListFileMenu->add(new MenuItem(L"New..."));
    menuListFileMenu->add(new MenuItem(L"Open..."));
    menuListFileMenu->add(new MenuItem(L"Save"));
    menuListFileMenu->add(new MenuItem(L"Save As..."));
    menuListMenu->add(menuListFileMenu);

    MenuItem* menuListEditMenu = new MenuItem(L"Edit");
    menuListEditMenu->add(new MenuItem(L"Cut"));
    menuListEditMenu->add(new MenuItem(L"Copy"));
    menuListEditMenu->add(new MenuItem(L"Paste"));
    menuListMenu->add(menuListEditMenu);
    MenuList* menuList = new MenuList(this, menuListMenu, true);


    //menuList->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_FILE), L"New..."));
    //menuList->addItem(new TextListItem(this, L"Open..."));
    //menuList->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_SAVE), L"Save"));
    //menuList->addItem(new TextListItem(this, L"Save As..."));
    menuButtonTab->add(menuList);
    m_tabs->addTab(L"Menu Test", menuButtonTab, true);

    Frame* listFrame = new Frame(this, true);
    listFrame->add(new Label(this, L"List:"));

    List* list = new List(this);
    list->contextMenuSignal().connect(sigc::mem_fun(*this, &DemoApp::onContextMenu));
    list->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_FOLDER_OPEN), L"This is"));
    list->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_THUMBS_UP), L"a list"));
    list->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_TOGGLE_ON), L"with lots"));
    list->addItem(new TextListItem(this, L"of very"));
    list->addItem(new TextListItem(this, L"boring"));
    list->addItem(new TextListItem(this, L"items"));

    TreeListItem* tree1;
    list->addItem(tree1 = new TreeListItem(this, getTheme()->getIcon(FRONTIER_ICON_TREE), L"It's a tree!"));
    tree1->addItem(new TextListItem(this, L"This tree"));
    tree1->addItem(new TextListItem(this, L"has lots"));
    tree1->addItem(new TextListItem(this, L"of very"));
    tree1->addItem(new TextListItem(this, L"exciting items!"));

    TreeListItem* tree2;
    tree1->addItem(tree2 = new TreeListItem(this, getTheme()->getIcon(FRONTIER_ICON_TREE), L"It's a tree IN A TREE!"));
    tree2->addItem(new TextListItem(this, L"Wow!"));

    int i;
    for (i = 0; i < 100; i++)
    {
        list->addItem(new TextListItem(this, getTheme()->getIcon(FRONTIER_ICON_FOLDER_OPEN), L"Another item!"));
    }

    Scroller* scroller = new Scroller(this);
    scroller->setChild(list);
    listFrame->add(scroller);
    rootFrame->add(listFrame);

    m_mainWindow = new FrontierWindow(this, L"Frontier Demo", WINDOW_NORMAL);
    m_mainWindow->setContent(rootFrame);

    m_mainWindow->show();

    m_tooltipWindow = new TooltipWindow(this);
    return true;
}

void DemoApp::onIconButton()
{
    log(DEBUG, "onIconButton: Here!");
}

void DemoApp::onTextButton1()
{
    log(DEBUG, "onTextButton: Here!");

    Vector2D widgetPos = m_textButton1->getAbsolutePosition();
    widgetPos.y += m_textButton1->getHeight();

    Vector2D screenPos = m_mainWindow->getScreenPosition(widgetPos);

    m_tooltipWindow->show();
    m_tooltipWindow->setPosition(screenPos);
}

void DemoApp::onTextButton2()
{
    m_tooltipWindow->hide();
}

void DemoApp::onCloseTab(Widget* tab)
{
    log(DEBUG, "onCloseTab: Closing tab: %p", tab);
    m_tabs->closeTab(tab);
}

void DemoApp::onContextMenu(ListItem* item, Geek::Vector2D pos)
{
    log(DEBUG, "onContextMenu: item=%p, pos=%d,%d", item, pos.x, pos.y);

    Menu* menu = new Menu();
    MenuItem* item1 = new MenuItem(L"Hello!");
    //closeItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeActiveTab));
    menu->add(item1);
    m_mainWindow->openContextMenu(pos, menu);
}

void DemoApp::onMenuItem(MenuItem* item)
{
    log(DEBUG, "onMenuItem: item=%p", item);
}

int main(int argc, char** argv)
{
    DemoApp app;

    app.init();

    app.main();

    return 0;
}

