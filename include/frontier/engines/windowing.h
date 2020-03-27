#ifndef __FRONTIER_ENGINES_WINDOWING__H_
#define __FRONTIER_ENGINES_WINDOWING__H_

#include <frontier/engines/embedded.h>
#include <deque>

namespace Frontier
{

class WindowingEngine : public EmbeddedEngine
{
 private:
    std::deque<FrontierWindow*> m_windowOrder;

 public:
    WindowingEngine(FrontierApp* app);
    virtual ~WindowingEngine();


    void showWindow(FrontierWindow* window);
    void hideWindow(FrontierWindow* window);
    FrontierWindow* windowAt(int x, int y);

    void mouseMotion(int x, int y);
    void mouseButton(int x, int y, int button, bool direction);

    const std::deque<FrontierWindow*>& getWindowOrder() { return m_windowOrder; }
};

class WindowingEngineWindow : public EmbeddedWindow
{
 private:

 public:
    WindowingEngineWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window);
    virtual ~WindowingEngineWindow();

    virtual bool init();

    virtual void show();
    virtual void hide();
};


};

#endif
