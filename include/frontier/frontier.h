#ifndef __FRONTIER_UI_H_
#define __FRONTIER_UI_H_

#include <vector>

#include <geek/gfx-surface.h>
#include <frontier/fonts.h>

class FrontierEngine;
class FrontierApp;
class Widget;

struct FrontierEngineWindow;

struct Message
{
    uint32_t messageType;
};

struct AppMessage : public Message
{
    uint32_t appMessageType;
};

#define FRONTIER_MSG_APP   1
#define FRONTIER_MSG_INPUT  2
#define FRONTIER_MSG_UI  3

#define FRONTIER_MSG_APP_QUIT 1

#define FRONTIER_MSG_INPUT_KEY 1
#define FRONTIER_MSG_INPUT_MOUSE_BUTTON 2
#define FRONTIER_MSG_INPUT_MOUSE_MOTION 3

struct InputMessage : public Message
{
    uint32_t inputMessageType;
    union
    {
        struct
        {
            bool direction;
            uint32_t key;
        } key;
        struct
        {
            uint32_t x;
            uint32_t y;
        } motion;
        struct
        {
            uint32_t x;
            uint32_t y;

            bool direction;
            uint8_t button;
            bool doubleClick;
        } button;
    } event;
};

#define FRONTIER_MSG_APP   1
#define FRONTIER_MSG_INPUT  2
#define FRONTIER_MSG_UI  3

#define FRONTIER_MSG_APP_QUIT 1

#define FRONTIER_MSG_INPUT_KEY 1
#define FRONTIER_MSG_INPUT_MOUSE_BUTTON 2
#define FRONTIER_MSG_INPUT_MOUSE_MOTION 3

struct UIMessage;

enum UIBorderType
{
    BORDER_WIDGET,
    BORDER_FRAME,
    BORDER_WINDOW
};

enum UIState
{
    STATE_NONE,
    STATE_SELECTED,
    STATE_HOVER
};

class UITheme
{
 protected:
    bool m_initialised;
    FontHandle* m_font;
    FontHandle* m_iconFont;
    FrontierApp* m_app;

 public:
    UITheme(FrontierApp* video);
    virtual ~UITheme();

    virtual bool init();

    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state, int x, int y, int w, int h);

    virtual void drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, bool inverted = false);
    virtual int getTextWidth(std::wstring text);
    virtual int getTextHeight();

    virtual void drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted = false);
    virtual int getIconWidth(wchar_t icon);
    virtual int getIconHeight();

    FrontierApp* getApp() { return m_app; }
};

struct UIMessage : public Message
{
    int uiMessageType;
    Widget* widget;
    Message* source;
    struct
    {
        bool state;
    } button;
    struct
    {
        int selected;
        int itemY;
    } list;
};

#define FRONTIER_MSG_UI_BUTTON_PRESSED 0x1000
#define FRONTIER_MSG_UI_LIST_SELECTED 0x2000

#define FRONTIER_ICON_CLOSE 0xf00d

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

    void postMessage(Message* message);
    virtual void handleMessage(Message* message);
};

class FrontierWindow
{
 private:
    FrontierApp* m_app;
    FrontierEngineWindow* m_engineWindow;

    Widget* m_widget;
    Widget* m_lastEventTarget;

    Geek::Gfx::Surface* m_surface;

    bool init();

 public:
    FrontierWindow(FrontierApp* app);
    ~FrontierWindow();

    void setContent(Widget* widget);

    void show();
    void update();

    void setEngineWindow(FrontierEngineWindow* few) { m_engineWindow = few; }
    FrontierEngineWindow* getEngineWindow() { return m_engineWindow; }

    int getWidth();
    int getHeight();
    Geek::Gfx::Surface* getSurface() { return m_surface; }

    void postMessage(Message* message);
    virtual bool handleMessage(Message* message);
};


#endif
