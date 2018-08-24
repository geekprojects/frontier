#ifndef __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_
#define __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_

#include <frontier/engine.h>

class CocoaEngine : public FrontierEngine
{
 private:
    void* m_application;

    bool createApplication();
    bool run();

 public:
    CocoaEngine(FrontierApp* app);
    virtual ~CocoaEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();
};

class CocoaWindow : public FrontierEngineWindow
{
 private:

    void* m_cocoaWindow;
    void* m_cocoaView;
    
    bool createCocoaWindow();
    bool drawSurface(Geek::Gfx::Surface* surface);

    Frontier::Size getSize();
    void setSize(Frontier::Size size);

 public:
    CocoaWindow(FrontierWindow* window);
    ~CocoaWindow();

    virtual bool init();
    virtual bool show();

    virtual bool update();

    virtual float getScaleFactor();
};

#endif
