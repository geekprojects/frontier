#ifndef __FRONTIER_CONTEXT_MENU_H_
#define __FRONTIER_CONTEXT_MENU_H_

#include <frontier/frontier.h>
#include <frontier/menu.h>
#include <frontier/widgets/list.h>

#include <vector>

namespace Frontier
{

class ContextMenu : public FrontierWindow
{
 private:
    Menu* m_menu;
    MenuList* m_menuList;

 public:
    ContextMenu(FrontierApp* app, Menu* menu = NULL);
    virtual ~ContextMenu();

    virtual bool init();

    void setMenu(Menu* menu);

    void lostFocus();

    void itemSelected(ListItem* item);
};

};

#endif
