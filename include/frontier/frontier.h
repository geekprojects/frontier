#ifndef __FRONTIER_UI_H_
#define __FRONTIER_UI_H_

#include <vector>

#include <geek/gfx-surface.h>

#include <frontier/utils.h>
#include <frontier/fonts.h>
#include <frontier/messages.h>
#include <frontier/theme.h>

namespace Frontier
{
class FrontierEngine;
class FrontierApp;
class Widget;
class UITheme;

class FrontierEngineWindow;

class FrontierApp
{
 private:
    FrontierEngine* m_engine;

    FontManager* m_fontManager;
    UITheme* m_theme;

 public:
    FrontierApp();
    virtual ~FrontierApp();

    FrontierEngine* getEngine() { return m_engine; }
    FontManager* getFontManager() { return m_fontManager; }
    UITheme* getTheme() { return m_theme; }

    virtual bool init();
    virtual bool main();

    void postMessage(Frontier::Message* message);
    virtual void handleMessage(Frontier::Message* message);

    std::string chooseFile();
};

class FrontierWindow
{
 private:
    FrontierApp* m_app;
    FrontierEngineWindow* m_engineWindow;

    Frontier::Size m_size;

    Widget* m_widget;
    Widget* m_activeWidget;

    Geek::Gfx::Surface* m_surface;

    bool init();

 public:
    FrontierWindow(FrontierApp* app);
    ~FrontierWindow();

    void setContent(Widget* widget);
    void setActiveWidget(Widget* widget) { m_activeWidget = widget; }

    void show();
    void update();

    void setEngineWindow(FrontierEngineWindow* few) { m_engineWindow = few; }
    FrontierEngineWindow* getEngineWindow() { return m_engineWindow; }

    void setSize(Frontier::Size size);
    Frontier::Size getSize() { return m_size; }
    Geek::Gfx::Surface* getSurface() { return m_surface; }

    void postMessage(Frontier::Message* message);
    virtual bool handleMessage(Frontier::Message* message);
};

};

#endif
