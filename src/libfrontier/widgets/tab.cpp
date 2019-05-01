
#include <frontier/frontier.h>
#include <frontier/widgets/tabs.h>

using namespace std;
using namespace Geek;
using namespace Frontier;

#define MAX_TAB_SIZE 250
#define TAB_SIZE 22

Tab::Tab(Tabs* tabs, wstring title, Icon* icon, Widget* content, bool closeable)
    : Widget(tabs->getApp(), L"Tab")
{
    m_tabs = tabs;

    m_title = title;
    m_icon = icon;
    m_content = content;
    m_closeable = closeable;

    m_content->setParent(m_tabs);
    m_content->incRefCount();
}

Tab::Tab(FrontierApp* app, wstring title, Icon* icon, Widget* content, bool closeable)
    : Widget(app, L"Tab")
{
    m_tabs = NULL;

    m_title = title;
    m_icon = icon;
    m_content = content;
    m_closeable = closeable;

    m_content->incRefCount();
}

Tab::~Tab()
{
    m_content->decRefCount();
}

void Tab::calculateSize()
{
    m_minSize.set(TAB_SIZE, TAB_SIZE);
    if (m_closeable)
    {
        m_minSize.width += TAB_SIZE;
    }

    m_maxSize.set(MAX_TAB_SIZE, TAB_SIZE);
}

void Tab::layout()
{
    // Our owning Tabs widget handles the content!
}

bool Tab::draw(Geek::Gfx::Surface* surface)
{
    UIState state = STATE_NONE;
    if (m_tabs != NULL && m_tabs->getActiveTab() == m_content)
    {
        state = STATE_SELECTED;
    }

    bool horizontal = true;
    int rotate = 0;
    if (m_tabs != NULL)
    {
        if (m_tabs->getTabPlacement() == TAB_LEFT)
        {
            rotate = 90;
            horizontal = false;
        }
        else if (m_tabs->getTabPlacement() == TAB_RIGHT)
        {
            rotate = 270;
            horizontal = false;
        }
    }

    m_app->getTheme()->drawBorder(
        surface,
        BORDER_TAB,
        state,
        0, 0,
        m_setSize.width, m_setSize.height);

    int titleWidth;
    if (horizontal)
    {
        titleWidth = m_setSize.width - 10;
    }
    else
    {
        titleWidth = m_setSize.height - 10;
    }


    int closeWidth = 0;
    if (m_closeable)
    {
        closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
        titleWidth -= closeWidth + 5;
    }

    int textOffsetX = 0;
    int textOffsetY = 0;
    Size iconSize;
    if (m_icon != NULL)
    {
        iconSize = m_icon->getSize();
        int iconX = 5;
        int iconY = 5;
        if (horizontal)
        {
            titleWidth -= iconSize.width + 5;
            textOffsetX = iconSize.width + 5;
            iconY = (m_setSize.height / 2) - (iconSize.height / 2);
        }
        else
        {
            titleWidth -= iconSize.height + 5;
            textOffsetY = iconSize.height + 5;
            iconX = (m_setSize.width / 2) - (iconSize.width / 2);
        }

        m_icon->draw(surface, iconX, iconY);
    }

    int labelHeight = m_app->getTheme()->getTextHeight();
    int labelY = ((TAB_SIZE / 2) - (labelHeight / 2));

    m_app->getTheme()->drawText(
        surface,
        textOffsetX + 5,
        textOffsetY + labelY,
        m_title.c_str(),
        titleWidth, false, rotate);

    if (m_closeable)
    {
        m_app->getTheme()->drawIcon(
            surface,
            m_setSize.width - (closeWidth + 5),
            labelY,
            FRONTIER_ICON_WINDOW_CLOSE,
            false);
    }

    return true;
}

Widget* Tab::handleEvent(Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {

        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        Vector2D thisPos = getAbsolutePosition();
        x -= thisPos.x;
        y -= thisPos.y;

        if (event->eventType == FRONTIER_EVENT_MOUSE_BUTTON)
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            if (m_closeable)
            {
                int closeWidth = m_app->getTheme()->getIconWidth(FRONTIER_ICON_WINDOW_CLOSE);
                if (x > m_setSize.width - (closeWidth + 5))
                {
                    if (!mouseButtonEvent->direction)
                    {
                        m_tabs->closeTabSignal().emit(m_content);
                    }

                    return this;
                }
            }

            if (mouseButtonEvent->buttons == BUTTON_RIGHT)
            {
                log(DEBUG, "handleMessage: CONTEXT MENU!!!");
                openContextMenu(Geek::Vector2D(mouseButtonEvent->x, mouseButtonEvent->y));
            }
            else if (!mouseButtonEvent->direction)
            {
                return NULL;
            }

            if (m_tabs != NULL)
            {
                m_tabs->setActiveTab(this);
            }

            return m_content;
        }
        else
        {
            return this;
        }
    }

    return NULL;
}


