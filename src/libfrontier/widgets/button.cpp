
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek::Gfx;

Button::Button(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_text = text;
    m_state = false;
}

Button::~Button()
{
}

void Button::calculateSize()
{
    m_width = m_ui->getTheme()->getTextWidth(m_text) + (5 * 2);
    m_height = m_ui->getTheme()->getTextHeight() + (5 * 2);

    m_dirty = false;
}

bool Button::draw(Surface* surface)
{
    int w = m_ui->getTheme()->getTextWidth(m_text);
    int x = (m_width / 2) - (w / 2);

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        m_state ? STATE_SELECTED : STATE_NONE,
        0, 0,
        m_width, m_height);
    m_ui->getTheme()->drawText(surface, x, 2, m_text);

    return true;
}

Widget* Button::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            printf("Button::handleMessage: Message! text=%ls\n", m_text.c_str());
            if (m_state != imsg->event.button.direction)
            {
                setDirty();
                m_state = imsg->event.button.direction;
                if (!m_state)
                {
                    UIMessage* buttonMessage = new UIMessage();
                    buttonMessage->messageType = FRONTIER_MSG_UI;
                    buttonMessage->uiMessageType = FRONTIER_MSG_UI_BUTTON_PRESSED;
                    buttonMessage->widget = this;
                    buttonMessage->source = msg;
                    buttonMessage->button.state = m_state;
                    m_ui->postMessage(buttonMessage);
                }
            }
        }
    }
    return this;
}

