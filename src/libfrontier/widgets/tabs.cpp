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
#include <frontier/widgets/tabs.h>
#include <frontier/fontawesome.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define MAX_TAB_SIZE 250
#define TAB_HEIGHT 22

Tabs::Tabs(FrontierApp* ui) : Widget(ui)
{
    m_activeTab = 0;
}

Tabs::Tabs(FrontierWindow* window) : Widget(window)
{
    m_activeTab = 0;
}

Tabs::~Tabs()
{
    for (Tab tab : m_tabs)
    {
        tab.content->decRefCount();
    }
    m_tabs.clear();
}

void Tabs::init()
{
    Menu* menu = new Menu();

    MenuItem* closeItem = new MenuItem(L"Close");
    closeItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeActiveTab));
    menu->add(closeItem);

    MenuItem* closeAllItem = new MenuItem(L"Close All");
    closeAllItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeAllTabs));
    menu->add(closeAllItem);

    MenuItem* closeOthersItem = new MenuItem(L"Close Others");
    closeOthersItem->clickSignal().connect(sigc::mem_fun(*this, &Tabs::closeAllButActiveTab));
    menu->add(closeOthersItem);

    setContextMenu(menu);
}

void Tabs::calculateSize()
{
    if (m_tabs.empty())
    {
        m_minSize.set(0, TAB_HEIGHT);
        m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
        return;
    }

    Widget* activeWidget = getActiveTab();
    if (activeWidget == NULL)
    {
        return;
    }

    activeWidget->calculateSize();

    Size activeMinSize = activeWidget->getMinSize();
    Size activeMaxSize = activeWidget->getMaxSize();

    activeMinSize.height += TAB_HEIGHT;

    activeMaxSize.width = WIDGET_SIZE_UNLIMITED;
    activeMaxSize.height += TAB_HEIGHT;

    m_minSize = activeMinSize;
    m_maxSize = activeMaxSize;

    int closeWidth = m_ui->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
    int tabsWidth = 0;
    for (Tab tab : m_tabs)
    {
        tabsWidth += 20;
        if (tab.closeable)
        {
            tabsWidth += closeWidth;
        }
    }

    if (m_minSize.width < tabsWidth)
    {
        m_minSize.width = tabsWidth;
    }
}

void Tabs::layout()
{
    if (m_tabs.empty())
    {
        return;
    }
    Widget* activeWidget = getActiveTab();

    Size tabSize = Size(m_setSize.width, m_setSize.height - TAB_HEIGHT);
    activeWidget->setSize(tabSize);
    activeWidget->setPosition(0, TAB_HEIGHT);
    activeWidget->layout();
}

bool Tabs::draw(Surface* surface)
{
    Widget::draw(surface);

    int labelHeight = m_ui->getTheme()->getTextHeight();
    int labelY = (TAB_HEIGHT / 2) - (labelHeight / 2);

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        STATE_NONE,
        0, TAB_HEIGHT,
        m_setSize.width, m_setSize.height - TAB_HEIGHT);

    if (m_tabs.empty())
    {
        return true;
    }

    int tabWidth = getTabWidth();

#if 0
    printf("Tabs::draw: tabs=%lu, titleWidth=%d\n", m_tabs.size(), titleWidth);
#endif

    int closeWidth = m_ui->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);

    vector<Tab>::iterator it;
    int x = 0;
    unsigned int tab;
    for (it = m_tabs.begin(), tab = 0; it != m_tabs.end(); it++, tab++)
    {
        //uint32_t backgroundCol;
        bool isActive = (tab == m_activeTab);
        UIState state = STATE_NONE;
        if (isActive)
        {
            //backgroundCol = 0xff808080;
            state = STATE_SELECTED;
        }
        else
        {
            //backgroundCol = m_ui->getTheme()->getColour(COLOUR_WINDOW_BACKGROUND);
        }
        //surface->drawRectFilled(x, 0, titleWidth - 1, 24, backgroundCol);

        m_ui->getTheme()->drawBorder(
            surface,
            BORDER_TAB,
            state,
            x, 0,
            tabWidth, TAB_HEIGHT);

        int titleWidth = tabWidth - 10;
        if (it->closeable)
        {
            titleWidth -= closeWidth + 5;
        }

#if 0
        printf("Tabs::draw:  -> %ls: active=%d x=%d, tabWidth=%d, titleWidth=%d, closeable=%d\n", it->title.c_str(), isActive, x, tabWidth, titleWidth, it->closeable);
#endif

        m_ui->getTheme()->drawText(
            surface,
            x + 5,
            labelY,
           it->title.c_str(),
            titleWidth); 

        if (it->closeable)
        {
            m_ui->getTheme()->drawIcon(
                surface,
                x + tabWidth - (closeWidth + 5),
                labelY,
                FRONTIER_ICON_WINDOW_CLOSE,
                false);
        }

        if (tab < m_tabs.size() - 1)
        {
            //surface->drawLine(x + tabWidth - 1, 0, x + tabWidth - 1, 24, 0xffffffff);
        }
        x += tabWidth;
    }

    Widget* activeWidget = m_tabs.at(m_activeTab).content;

    SurfaceViewPort viewport(surface, activeWidget->getX(), activeWidget->getY(), activeWidget->getWidth(), activeWidget->getHeight());
    return activeWidget->draw(&viewport);
}

Widget* Tabs::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        switch (imsg->inputMessageType)
        {
            case FRONTIER_MSG_INPUT_MOUSE_BUTTON:
            case FRONTIER_MSG_INPUT_MOUSE_MOTION:
            case FRONTIER_MSG_INPUT_MOUSE_WHEEL:
            {
                int x = imsg->event.button.x;
                int y = imsg->event.button.y;

                Vector2D thisPos = getAbsolutePosition();
                x -= thisPos.x;
                y -= thisPos.y;

                if (y < TAB_HEIGHT)
                {
                    if (imsg->inputMessageType != FRONTIER_MSG_INPUT_MOUSE_BUTTON)
                    {
                        return this;
                    }

                    if (m_tabs.empty())
                    {
                        return this;
                    }


                    int tabWidth = getTabWidth();
                    unsigned int tab = 0;

                    if (tabWidth > 0)
                    {
                        tab = x / tabWidth;
                    }

#if 0
                    printf("Tabs::handleMessage: x=%d, titleWidth=%d, m_activeTab=%d\n", x, titleWidth, m_activeTab);
#endif
                    if (tab >= m_tabs.size())
                    {
                        return NULL;
                    }

                    Widget* activeTab = getActiveTab();

                    if (m_tabs.at(tab).closeable)
                    {
                        int closeWidth = m_ui->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
                        if (x > (int)((tab * tabWidth) + (tabWidth - (closeWidth + 5))))
                        {
                            if (!imsg->event.button.direction)
                            {
                                m_closeTabSignal.emit(m_tabs.at(tab).content);
                            }

                            return this;
                        }
                    }

                    if (imsg->event.button.buttons == BUTTON_RIGHT)
                    {
                        printf("Tabs::handleMessage: CONTEXT MENU!!!\n");
                        openContextMenu(Geek::Vector2D(imsg->event.button.x, imsg->event.button.y));
                    }
                    else if (!imsg->event.button.direction)
                    {
                        return NULL;
                    }

                    m_activeTab = tab;
                    activeTab = getActiveTab();

                    setDirty();

#if 0
                    printf("Tabs::handleMessage: activeTab=%p\n", activeTab);
#endif

                    m_changeTabSignal.emit(activeTab);
                    if (activeTab != NULL)
                    {
                        activeTab->setDirty();
                        return activeTab;
                    }
                    else
                    {
                        return this;
                    }
                }
                else if (!m_tabs.empty())
                {
                    Widget* activeWidget = m_tabs.at(m_activeTab).content;

                    if (activeWidget != NULL)
                    {
                        return activeWidget->handleMessage(msg);
                    }

                }
            } break;
            default:
                break;
        }
    }
    return NULL;
}

void Tabs::addTab(std::wstring title, Widget* content, bool closeable)
{
    Tab tab;
    tab.title = title;
    tab.content = content;
    tab.closeable = closeable;

    m_tabs.push_back(tab);

    content->incRefCount();
    content->setParent(this);

    setDirty();
}

void Tabs::closeTab(Widget* widget, bool emitChangeSignal)
{
    vector<Tab>::iterator it;

    unsigned int i;
    for (i = 0, it = m_tabs.begin(); it != m_tabs.end(); it++, i++)
    {
        if (it->content == widget)
        {
            bool isActive = (i == m_activeTab);

            it->content->decRefCount();
            m_tabs.erase(it);

            if (m_activeTab >= m_tabs.size())
            {
                m_activeTab = m_tabs.size() - 1;
            }

            if (isActive && emitChangeSignal)
            {
                m_changeTabSignal.emit(getActiveTab());
            }

            layout();
            setDirty();
            return;
        }
    }
}

void Tabs::closeActiveTab()
{
    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        closeTab(activeWidget);
    }
}

void Tabs::closeAllTabs()
{
    vector<Tab> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab tab : tabs)
    {
        if (tab.closeable)
        {
            closeTab(tab.content, false);
        }
    }
}

void Tabs::closeAllButActiveTab()
{
    Widget* activeWidget = getActiveTab();

    vector<Tab> tabs  = m_tabs; // Make a copy as the original will be modified
    for (Tab tab : tabs)
    {
        if (tab.closeable && tab.content != activeWidget)
        {
            closeTab(tab.content, false);
        }
    }
}

void Tabs::setActiveTab(Widget* tabContent)
{
    int i = 0;
    for (Tab tab : m_tabs)
    {
        if (tab.content == tabContent)
        {
            m_activeTab = i;

            layout();
            setDirty();
            return;
        }
        i++;
    }

    return;
}

int Tabs::findTab(Widget* tabContent)
{
    int i = 0;
    for (Tab tab : m_tabs)
    {
        if (tab.content == tabContent)
        {
            return i;
        }
        i++;
    }

    // Not found
    return -1;
}

void Tabs::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }
    printf("%s: %p: x=%d, y=%d, size=%s\n", spaces.c_str(), this, m_x, m_y, m_setSize.toString().c_str());

    Widget* activeWidget = getActiveTab();
    if (activeWidget != NULL)
    {
        activeWidget->dump(level + 1);
    }
}

int Tabs::getTabWidth()
{
    if (m_tabs.empty())
    {
        return 0;
    }

    int tabWidth = m_setSize.width / m_tabs.size();
    if (tabWidth > MAX_TAB_SIZE)
    {
        tabWidth = MAX_TAB_SIZE;
    }
    return tabWidth;
}

