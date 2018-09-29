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
#include <frontier/widgets.h>

using namespace Frontier;

class DemoApp : public FrontierApp
{
 private:
    FrontierWindow* m_mainWindow;

    void onTextButton();
    void onIconButton();

 public:
    DemoApp();
    ~DemoApp();

    virtual bool init();
};

using namespace Frontier;

DemoApp::DemoApp()
{
}

DemoApp::~DemoApp()
{
}

bool DemoApp::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    Frame* rootFrame = new Frame(this, false);
    Tabs* tabs = new Tabs(this);
    rootFrame->add(tabs);

    Frame* toolbarTab = new Frame(this, false);

    Frame* toolbar1 = new Frame(this, true);
    toolbar1->add(new IconButton(this, FRONTIER_ICON_FOLDER_OPEN));
    toolbar1->add(new IconButton(this, FRONTIER_ICON_SAVE));
    toolbar1->add(new IconButton(this, FRONTIER_ICON_SYNC));
    toolbarTab->add(toolbar1);
    tabs->addTab(L"Tool Bars", toolbarTab);

    /*
     * Labels
     */
    Frame* labelTab = new Frame(this, false);
    tabs->addTab(L"Labels", labelTab);

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
    Button* textButton;
    buttonFrame1->add(new Label(this, L"Button:"));
    buttonFrame1->add(textButton = new Button(this, L"Click me!"));
    buttonTab->add(buttonFrame1);
    tabs->addTab(L"Buttons", buttonTab);

    Frame* iconButtonTab = new Frame(this, false);
    Frame* iconButtonFrame1 = new Frame(this, true);
    IconButton* iconButton;
    iconButtonFrame1->add(new Label(this, L"Icon Button:"));
    iconButtonFrame1->add(iconButton = new IconButton(this, 0xf0ae));
    iconButtonTab->add(iconButtonFrame1);
tabs->addTab(L"Icon Buttons", iconButtonTab);

    textButton->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onTextButton));
    iconButton->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onIconButton));

    Frame* listFrame = new Frame(this, true);
    listFrame->add(new Label(this, L"List:"));

    List* list = new List(this);
    list->addItem(new TextListItem(this, FRONTIER_ICON_FOLDER_OPEN, L"This is"));
    list->addItem(new TextListItem(this, FRONTIER_ICON_CARET_RIGHT, L"a list"));
    list->addItem(new TextListItem(this, L"with lots"));
    list->addItem(new TextListItem(this, L"of very"));
    list->addItem(new TextListItem(this, L"boring"));
    list->addItem(new TextListItem(this, L"items"));

    TreeListItem* tree1;
    list->addItem(tree1 = new TreeListItem(this, FRONTIER_ICON_TREE, L"It's a tree!"));
    tree1->addItem(new TextListItem(this, L"This tree"));
    tree1->addItem(new TextListItem(this, L"has lots"));
    tree1->addItem(new TextListItem(this, L"of very"));
    tree1->addItem(new TextListItem(this, L"exciting items!"));

    TreeListItem* tree2;
    tree1->addItem(tree2 = new TreeListItem(this, FRONTIER_ICON_TREE, L"It's a tree IN A TREE!"));
    tree2->addItem(new TextListItem(this, L"Wow!"));

    Scroller* scroller = new Scroller(this);
    scroller->setChild(list);
    listFrame->add(scroller);
    rootFrame->add(listFrame);

    m_mainWindow = new FrontierWindow(this);
    m_mainWindow->setContent(rootFrame);

    m_mainWindow->show();

    return true;
}

void DemoApp::onIconButton()
{
    printf("DemoApp::onIconButton: Here!\n");
}

void DemoApp::onTextButton()
{
    printf("DemoApp::onTextButton: Here!\n");
}

int main(int argc, char** argv)
{
    DemoApp app;

    app.init();

    app.main();

    return 0;
}

