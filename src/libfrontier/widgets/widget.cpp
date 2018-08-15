
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui)
{
    m_ui = ui;
    m_parent = NULL;

    m_dirty = true;

    m_minWidth = 0;
    m_minHeight = 0;
    m_margin = 5;
    m_padding = 5;
}

Widget::~Widget()
{
}

void Widget::calculateSize()
{
}

bool Widget::draw(Geek::Gfx::Surface* surface)
{
    return true;
}

Geek::Vector2D Widget::getAbsolutePosition()
{
    Vector2D pos;
    pos.x = m_x;
    pos.y = m_y;

    if (m_parent != NULL)
    {
        pos += m_parent->getAbsolutePosition();
    }
    else
    {
        //pos += m_ui->getPosition();
    }

    return pos;
}

bool Widget::intersects(int x, int y)
{
    Vector2D thisPos = getAbsolutePosition();
    int x1 = thisPos.x;
    int y1 = thisPos.y;
    int x2 = x1 + getWidth();
    int y2 = y1 + getHeight();
    return (x >= x1 && y >= y1 && x < x2 && y < y2);
}

void Widget::setDirty()
{
    m_dirty = true;
    if (m_parent != NULL)
    {
        m_parent->setDirty();
    }
}

Widget* Widget::handleMessage(Message* msg)
{
    return NULL;
}

