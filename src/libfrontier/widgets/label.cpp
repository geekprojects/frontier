
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek::Gfx;

Label::Label(FrontierApp* ui, wstring text) : Widget(ui)
{
    m_text = text;
}

Label::~Label()
{
}

void Label::setText(std::wstring text)
{
    m_text = text;
    setDirty();
}

void Label::calculateSize()
{
    m_lineHeight = m_ui->getTheme()->getTextHeight();

    m_minSize.set(0, 0);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    int pos = 0;
    int lines = 0;
    wstring line = L"";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n' || pos == m_text.length() - 1)
        {
            lines++;
            if (pos == m_text.length() - 1)
            {
                line += m_text[pos];
            }
            int w = m_ui->getTheme()->getTextWidth(line);
            if (w > m_minSize.width)
            {
                m_minSize.width = w;
            }
            line = L"";
        }
        else
        {
            line += m_text[pos];
        }
    }

    m_minSize.width += (5 * 2);
    m_minSize.height = (m_lineHeight * lines) + (5 * 2);

m_maxSize.height = m_minSize.height;

    m_dirty = false;
}

bool Label::draw(Surface* surface)
{
    Widget::draw(surface);

    int y = 5;

    int pos = 0;

    int lines = 1;
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n')
        {
            lines++;
        }
    }

    y = (m_setSize.height / 2) - (lines * m_lineHeight) / 2;
 
    wstring line = L"";
    for (pos = 0; pos < m_text.length(); pos++)
    {
        if (m_text[pos] == '\n' || pos == m_text.length() - 1)
        {
            if (pos == m_text.length() - 1)
            {
                line += m_text[pos];
            }
            int w = m_ui->getTheme()->getTextWidth(line);
            int x = (m_setSize.width / 2) - (w / 2);

            m_ui->getTheme()->drawText(
                surface,
                x,
                y,
                line.c_str());
 
            y += m_lineHeight;
            line = L"";
        }
        else
        {
            line += m_text[pos];
        }
    }

   return true;
}

Widget* Label::handleMessage(Message* msg)
{
    // We just swallow events
    return NULL;
}

