
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek::Gfx;

IconButton::IconButton(FrontierApp* ui, wchar_t icon) : Button(ui, L"")
{
    m_icon = icon;
    m_state = false;
}

IconButton::~IconButton()
{
}

void IconButton::calculateSize()
{
    m_width = m_ui->getTheme()->getIconWidth(m_icon) + (5 * 2);
    m_height = m_ui->getTheme()->getIconHeight() + (5 * 2);

    m_dirty = false;
}

bool IconButton::draw(Surface* surface)
{
    int w = m_ui->getTheme()->getIconWidth(m_icon);
    int h = m_ui->getTheme()->getIconHeight();
    int x = (m_width / 2) - (w / 2);
    int y = (m_height / 2) - (h / 2);

    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_WIDGET,
        m_state ? STATE_SELECTED : STATE_NONE,
        0, 0,
        m_width, m_height);
    m_ui->getTheme()->drawIcon(surface, x, y, m_icon);

    return true;
}

