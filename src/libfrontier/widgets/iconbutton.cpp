
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
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
    m_minSize.width = m_ui->getTheme()->getIconWidth(m_icon) + (5 * 2);
    m_minSize.height = m_ui->getTheme()->getIconHeight() + (5 * 2);

if (m_minSize.height > m_minSize.width)
{
m_minSize.width = m_minSize.height;
}

//    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);
m_maxSize = m_minSize;

    m_dirty = false;
}

bool IconButton::draw(Surface* surface)
{
    int w = m_ui->getTheme()->getIconWidth(m_icon);
    int h = m_ui->getTheme()->getIconHeight();
    int x = (m_setSize.width / 2) - (w / 2);
    int y = (m_setSize.height / 2) - (h / 2);

if (m_state)
{
    m_ui->getTheme()->drawBorder(
        surface,
        BORDER_BUTTON,
        m_state ? STATE_SELECTED : STATE_NONE,
        0, 0,
        m_setSize.width, m_setSize.height);
}

    m_ui->getTheme()->drawIcon(surface, x, y, m_icon);

    return true;
}

