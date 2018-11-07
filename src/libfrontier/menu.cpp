
#include <frontier/menu.h>

using namespace Frontier;

Menu::Menu()
{
}

Menu::~Menu()
{
}


MenuItem::MenuItem(std::wstring title)
{
    m_title = title;
}

MenuItem::~MenuItem()
{
    for (MenuItem* child : m_children)
    {
        delete child;
    }

    m_children.clear();
}

void MenuItem::add(MenuItem* child)
{
    m_children.push_back(child);
}


