
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek;
using namespace Geek::Gfx;

List::List(FrontierApp* ui) : Widget(ui)
{
    m_selected = -1;
}

List::~List()
{
}

void List::calculateSize()
{
    vector<ListItem*>::iterator it;
    m_width = 50;
    for (it = m_list.begin(); it != m_list.end(); it++)
    {
        ListItem* item = *it;
        int w = m_ui->getTheme()->getTextWidth(item->getText()) + (5 * 2);
        if (w > m_width)
        {
            m_width = w;
        }
    }

    m_itemHeight = m_ui->getTheme()->getTextHeight();
    m_height = m_itemHeight * m_list.size();

    m_width += 2 * 2;
    m_height += 2 * 2;

    m_dirty = false;
}

bool List::draw(Surface* surface)
{
    surface->drawRect(0, 0, m_width, m_height, 0xffffffff);

    int x = 2;
    int y = 2;
    int idx;
    vector<ListItem*>::iterator it;
    for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
    {
        ListItem* item = *it;
        uint32_t c = 0xffffffff;
        if (m_selected == idx)
        {
            c = 0xff000000;
            surface->drawRectFilled(0, y, m_width, m_itemHeight, 0xffffffff);
        }

        m_ui->getTheme()->drawText(surface, x, y, item->getText(), m_selected == idx);

        if (it + 1 != m_list.end())
        {
            surface->drawLine(0, y + m_itemHeight, m_width, y + m_itemHeight, 0xffffffff);
        }

        y += m_itemHeight;
    }
    return true;
}

Widget* List::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            Vector2D pos = getAbsolutePosition();
            int ey = imsg->event.button.y - pos.y;
            int selected = -1;
            bool hasSelected = false;
            int y = 2;

            int idx;
            vector<ListItem*>::iterator it;
            for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
            {
                ListItem* item = *it;
                if (ey >= y && ey < y + m_itemHeight)
                {
                    selected = idx;
                    hasSelected = true;
                    break;
                }
                y += m_itemHeight;
            }

            if (hasSelected && (m_selected != selected || imsg->event.button.doubleClick || imsg->event.button.button == 3))
            {
                printf("List::handleMessage: Selected item %d, doubleClick=%d\n", m_selected, imsg->event.button.doubleClick);

                setDirty();

                m_selected = selected;

                UIMessage* buttonMessage = new UIMessage();
                buttonMessage->messageType = FRONTIER_MSG_UI;
                buttonMessage->uiMessageType = FRONTIER_MSG_UI_LIST_SELECTED;
                buttonMessage->widget = this;
                buttonMessage->source = msg;
                buttonMessage->list.selected = m_selected;
                buttonMessage->list.itemY = y;
                m_ui->postMessage(buttonMessage);
            }
        }
    }

    return this;
}

void List::clearItems()
{
    m_list.clear();
    setDirty();
}

void List::addItem(ListItem* item)
{
    m_list.push_back(item);
    setDirty();
}

