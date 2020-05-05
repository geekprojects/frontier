
#include <frontier/contextmenu.h>
#include <frontier/widgets/list.h>
#include <frontier/widgets/frame.h>

using namespace std;
using namespace Frontier;
using namespace Geek;


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
    Frame* frame = new Frame(this, false);

    m_menuList = new MenuList(this, m_menu);
    m_menuList->selectSignal().connect(sigc::mem_fun(*this, &ContextMenu::itemSelected));
    frame->add(m_menuList);

    setContent(frame);

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
    log(DEBUG, "itemSelected: %ls", menuItem->getTitle().c_str());

    menuItem->clickSignal().emit(menuItem);

    hide();
}

