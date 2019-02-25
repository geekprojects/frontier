
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
    m_key = 0;
    m_keyModifiers = 0;
    m_isSeparator = false;
}

MenuItem::MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers)
{
    m_title = title;
    m_key = key;
    m_keyModifiers = keyModifiers;
    m_isSeparator = false;
}

MenuItem::~MenuItem()
{
    for (MenuItem* child : m_children)
    {
        delete child;
    }

    m_children.clear();
}

void MenuItem::setIsSeparator(bool isSeparator)
{
    m_isSeparator = isSeparator;
}

void MenuItem::add(MenuItem* child)
{
    m_children.push_back(child);
}

MenuSeparator::MenuSeparator() : MenuItem(L"")
{
    setIsSeparator(true);
}

MenuSeparator::~MenuSeparator()
{
}


