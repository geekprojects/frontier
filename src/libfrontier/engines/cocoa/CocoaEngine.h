#ifndef __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_
#define __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_

#include <frontier/engine.h>

namespace Frontier {

class CocoaEngine : public FrontierEngine
{
 private:
    void* m_application;
    void* m_appDelegate;
    void* m_windowMenu;

    Menu* m_currentMenu;

    bool createApplication();
    bool run();

    void updateMenu(Menu* menu);

    void onActiveWindowChanged(FrontierWindow* window);

 public:
    CocoaEngine(FrontierApp* app);
    virtual ~CocoaEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);


    virtual bool checkEvents();

    virtual std::string getConfigDir();

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);

    bool providesMenus() { return true; }

    void updateMenu(FrontierWindow* window);
};

}

#endif

