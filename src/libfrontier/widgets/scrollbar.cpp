
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek;
using namespace Geek::Gfx;

ScrollBar::ScrollBar(FrontierApp* ui) : Widget(ui)
{
    m_min = 0;
    m_max = 30;
    m_pos = 0;
    m_size = 10;
    m_preferredLength = 200;
    m_dragging = false;
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::calculateSize()
{
    m_width = 20;
    m_height = m_preferredLength;
    m_dirty = false;
}

bool ScrollBar::draw(Surface* surface)
{
int drawHeight = m_height - (3 * 2);
int drawWidth = m_width - (3 * 2);

    surface->drawRect(0, 0, m_width, m_height, 0xffffffff);

int pos = getControlPos();
//printf("ScrollBar::draw: m_pos=%d, pos=%d\n", m_pos, pos);
int sizePix = getControlSize();
//printf("ScrollBar::draw: sizePix=%d\n", sizePix);

    surface->drawRectFilled(3, pos + 3, drawWidth, sizePix, 0xffffffff);

    return true;
}

Widget* ScrollBar::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            Vector2D thisPos = getAbsolutePosition();

            int pos = getControlPos();
            int sizePix = getControlSize();

            int y = imsg->event.button.y - thisPos.y;
            y -= 3;

if (imsg->event.button.direction)
{
if (y >= pos && y < pos + sizePix)
{
//printf("ScrollBar::handleMessage: Control!!\n");
    m_dragging = true;
}
}
else
{
    m_dragging = false;
}

/*
                setDirty();

                m_state = imsg->event.button.direction;
                UIMessage* buttonMessage = new UIMessage();
                buttonMessage->messageType = FRONTIER_MSG_UI;
                buttonMessage->uiMessageType = FRONTIER_MSG_UI_BUTTON_PRESSED;
                buttonMessage->widget = this;
                buttonMessage->source = msg;
                buttonMessage->button.state = m_state;
                m_ui->postMessage(buttonMessage);
*/
        }
        else if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_MOTION)
        {
if (m_dragging)
{
//printf("ScrollBar::handleMessage: Drag!!\n");
            Vector2D thisPos = getAbsolutePosition();

int range = m_max - (m_min + m_size);
//int pos = (int)(((float)m_pos / (float)m_max) * (float)(m_height - 3));

int y = imsg->event.motion.y - thisPos.y;
//printf("ScrollBar::handleMessage: y=%d\n", y);

float r = (float)(y - 3) / (float)(m_height - (3 * 2));
//printf("ScrollBar::handleMessage: r=%0.2f\n", r);
m_pos = (int)((float)range * r) + m_min;
//printf("ScrollBar::handleMessage: m_pos=%d\n", m_pos);

if (m_pos < m_min)
{
m_pos = m_min;
}
else if (m_pos > (m_max - m_size))
{
m_pos = m_max - m_size;
}
//printf("ScrollBar::handleMessage: m_pos(2)=%d\n", m_pos);

setDirty();

}
}
    }

    return this;
}

void ScrollBar::set(int min, int max, int size)
{
    m_min = min;
    m_max = max;
    m_size = size;

    if (m_size > (m_max - m_min))
    {
        m_size = m_max - m_min;
        m_pos = 0;
    }
    if (m_pos > (m_max - m_size))
    {
        m_pos = m_max - m_size;
    }
    setDirty();
}

void ScrollBar::setPos(int pos)
{
    m_pos = pos;
    if (m_pos > (m_max - m_size))
    {
        m_pos = m_max - m_size;
    }
    setDirty();
}

int ScrollBar::getPos()
{
    return m_pos;
}

int ScrollBar::getControlPos()
{
int range = m_max - (m_min + m_size);
int pos = (int)(((float)(m_pos) / (float)m_max) * (float)(m_height - (3 * 2)));
return pos;
}

int ScrollBar::getControlSize()
{
//int range = m_max - (m_min + m_size);
int sizePix = (int)(((float)m_size / (float)m_max) * (float)(m_height - (3 * 2)));
return sizePix;
}

