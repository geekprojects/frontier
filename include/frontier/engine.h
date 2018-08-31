#ifndef __FRONTIER_ENGINE_H_
#define __FRONTIER_ENGINE_H_

#include <frontier/frontier.h>

#include <geek/core-logger.h>

namespace Frontier {

class FrontierEngine : public Geek::Logger
{
 private:
    FrontierApp* m_app;

 public:
    FrontierEngine(FrontierApp* app);
    virtual ~FrontierEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual std::string chooseFile();
};

class FrontierEngineWindow
{
 protected:
    FrontierWindow* m_window;

 public:
    FrontierEngineWindow(FrontierWindow* window);
    virtual ~FrontierEngineWindow();

    virtual bool init();
    virtual bool show();

    virtual bool update();

    FrontierWindow* getWindow() { return m_window; }

    virtual float getScaleFactor();
};

};

#endif
