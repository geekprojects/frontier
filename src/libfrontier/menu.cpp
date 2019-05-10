
#include <frontier/menu.h>

using namespace std;
using namespace Frontier;

Menu::Menu()
{
}

Menu::Menu(vector<MenuItem*> items)
{
    m_menuItems = items;
}

Menu::~Menu()
{
}


MenuItem::MenuItem(std::wstring title)
{
    init(title, 0, 0, false);
}

MenuItem::MenuItem(std::wstring title, sigc::slot<void, MenuItem*> clickSignalSlot)
{
    init(title, 0, 0, false);

    m_clickSignal.connect(clickSignalSlot);
}

MenuItem::MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers)
{
    init(title, key, keyModifiers, false);
}

MenuItem::MenuItem(std::wstring title, wchar_t key, uint32_t keyModifiers, sigc::slot<void, MenuItem*> clickSignalSlot)
{
    init(title, key, keyModifiers, false);

    m_clickSignal.connect(clickSignalSlot);
}

MenuItem::~MenuItem()
{
    for (MenuItem* child : m_children)
    {
        delete child;
    }

    m_children.clear();
}

void MenuItem::init(wstring title, wchar_t key, uint32_t keyModifiers, bool isSeparator)
{
    m_title = title;
    m_key = key;
    m_keyModifiers = keyModifiers;
    m_isSeparator = isSeparator;
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


