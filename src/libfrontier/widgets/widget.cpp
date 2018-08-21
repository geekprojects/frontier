
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui)
{
    m_ui = ui;
    m_parent = NULL;

    m_dirty = true;

    m_minSize = Size(0, 0);
    m_maxSize = Size(0, 0);
    m_setSize = Size(0, 0);

    m_margin = 5;
    m_padding = 5;
}

Widget::~Widget()
{
}

void Widget::calculateSize()
{
printf("Widget::calculateSize: Not set!\n");
}

void Widget::layout()
{
}

Size Widget::setSize(Size size)
{
    calculateSize();

    // Clip the specified size to our min/max
    size.setMax(m_minSize);
    size.setMin(m_maxSize);

    m_setSize = size;

    return size;
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

void Widget::dump(int level)
{
    string spaces = "";
int i;
for (i = 0; i < level; i++)
{
    spaces += "    ";
}
printf("%s: %p: x=%d, y=%d, size=%s\n", spaces.c_str(), this, m_x, m_y, m_setSize.toString().c_str());

vector<Widget*>::iterator it;
for (it = m_children.begin(); it != m_children.end(); it++)
{
(*it)->dump(level + 1);
}

}


