#ifndef __FRONTIER_MENU_H_
#define __FRONTIER_MENU_H_

namespace Frontier
{

class MenuItem
{
 private:

    sigc::signal<void> m_clickSignal;

 public:
    MenuItem(std::string title);
    virtual ~MenuItem();

    virtual sigc::signal<void> clickSignal() { return m_clickSignal; }
};

class Menu
{
 private:


 public:
    Menu(std::string title);
    virtual ~Menu();
};

};

#endif
