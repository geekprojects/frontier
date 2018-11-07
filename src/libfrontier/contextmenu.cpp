
#include <frontier/contextmenu.h>
#include <frontier/widgets/list.h>

using namespace std;
using namespace Frontier;


ContextMenu::ContextMenu(FrontierApp* app, Menu* menu) : FrontierWindow(app, L"", 0)
{
    m_menu = NULL;
    m_menuList = NULL;
}

ContextMenu::~ContextMenu()
{
}

bool ContextMenu::init()
{
    m_menuList = new MenuList(this, m_menu);
    m_menuList->selectSignal().connect(sigc::mem_fun(*this, &ContextMenu::itemSelected));
    setContent(m_menuList);
    return true;
}

void ContextMenu::setMenu(Menu* menu)
{
    if (m_menuList == NULL)
    {
        init();
    }

    m_menu = menu;
    if (m_menu == NULL)
    {
        m_menuList->clearItems();
        return;
    }

    m_menuList->setMenu(m_menu->getMenuItems());
}

void ContextMenu::lostFocus()
{
    hide();
}

void ContextMenu::itemSelected(ListItem* item)
{
    MenuItem* menuItem = (MenuItem*)(item->getPrivateData());
    printf("ContextMenu::itemSelected: %ls\n", menuItem->getTitle().c_str());

    menuItem->clickSignal().emit();

    hide();
}

