
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

#define MAX_TAB_SIZE 250

Tabs::Tabs(FrontierApp* ui) : Widget(ui)
{
    m_activeTab = 0;
}

Tabs::~Tabs()
{
}

void Tabs::calculateSize()
{
    if (m_tabs.empty())
    {
        m_minSize.set(0, 25);
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

    activeMinSize.height += 25;

    activeMaxSize.width = WIDGET_SIZE_UNLIMITED;
    activeMaxSize.height += 25;

    m_minSize = activeMinSize;
    m_maxSize = activeMaxSize;

    m_dirty = false;
}

void Tabs::layout()
{
    if (m_tabs.empty())
    {
        return;
    }
    Widget* activeWidget = getActiveTab();

    Size tabSize = Size(m_setSize.width, m_setSize.height - 25);
    activeWidget->setSize(tabSize);
    activeWidget->setPosition(0, 25);
    activeWidget->layout();
}

bool Tabs::draw(Surface* surface)
{
    Widget::draw(surface);
    if (m_tabs.empty())
    {
        return true;
    }

    int labelHeight = m_ui->getTheme()->getTextHeight();
    int labelY = (25 / 2) - (labelHeight / 2);

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        STATE_NONE,
        0, 25,
        m_setSize.width, m_setSize.height - 25);

    int titleWidth = getTabWidth();

    printf("Tabs::draw: tabs=%lu, titleWidth=%d\n", m_tabs.size(), titleWidth);

    vector<Tab>::iterator it;
    int x = 0;
    int tab;
    for (it = m_tabs.begin(), tab = 0; it != m_tabs.end(); it++, tab++)
    {
        uint32_t backgroundCol;
        bool isActive = (tab == m_activeTab);
        if (isActive)
        {
            backgroundCol = 0xff808080;
        }
        else
        {
            backgroundCol = m_ui->getTheme()->getColour(COLOUR_WINDOW_BACKGROUND);
        }
        surface->drawRectFilled(x, 0, titleWidth - 1, 24, backgroundCol);
        m_ui->getTheme()->drawBorder(
            surface,
            BORDER_WIDGET,
            STATE_NONE,
            x, 0,
            titleWidth, 24);

        printf("Tabs::draw:  -> %ls: active=%d x=%d\n", it->title.c_str(), isActive, x);

        m_ui->getTheme()->drawText(
            surface,
            x,
            labelY,
           it->title.c_str()); 

        if (tab < m_tabs.size() - 1)
        {
            //surface->drawLine(x + titleWidth - 1, 0, x + titleWidth - 1, 24, 0xffffffff);
        }
        x += titleWidth;
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
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            int x = imsg->event.button.x;
            int y = imsg->event.button.y;

            Vector2D thisPos = getAbsolutePosition();
            x -= thisPos.x;
            y -= thisPos.y;

            if (y < 25)
            {
                if (m_tabs.empty())
                {
                    return this;
                }

                if (!imsg->event.button.direction)
                {
                    return NULL;
                }

                int titleWidth = getTabWidth();
                int tab = x / titleWidth;
                printf("Tabs::handleMessage: x=%d, titleWidth=%d, m_activeTab=%d\n", x, titleWidth, m_activeTab);
                if (tab >= m_tabs.size())
                {
                    return NULL;
                }
                m_activeTab = tab;

                setDirty();

                Widget* activeTab = getActiveTab();
                printf("Tabs::handleMessage: activeTab=%p\n", activeTab);

                m_changeTabSignal.emit(activeTab);
                if (activeTab != NULL)
                {
                    getActiveTab()->setDirty();
                    return activeTab;
                }
                else
                {
                    return this;
                }
            }
            else
            {
                Widget* activeWidget = m_tabs.at(m_activeTab).content;

                if (activeWidget != NULL)
                {
                    return activeWidget->handleMessage(msg);
                }

            }
        }
    }
    return NULL;
}

void Tabs::addTab(std::wstring title, Widget* content)
{
    Tab tab;
    tab.title = title;
    tab.content = content;
    m_tabs.push_back(tab);

    content->setParent(this);

    setDirty();
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

