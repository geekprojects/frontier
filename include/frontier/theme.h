#ifndef __FRONTIER_THEME_H_
#define __FRONTIER_THEME_H_

#include <geek/gfx-surface.h>

#include <frontier/fonts.h>

namespace Frontier
{

class FrontierApp;

enum UIBorderType
{
    BORDER_WIDGET,
    BORDER_BUTTON,
    BORDER_FRAME,
    BORDER_WINDOW,
    BORDER_SCROLLBAR,
    BORDER_SCROLLBAR_CONTROL,
    BORDER_LIST_BACKGROUND,
    BORDER_LIST_ITEM_1,
    BORDER_LIST_ITEM_2,
};

enum UIState
{
    STATE_NONE,
    STATE_SELECTED,
    STATE_HOVER
};

enum ThemeColour
{
    COLOUR_WINDOW_BACKGROUND,
    COLOUR_BUTTON_1,
    COLOUR_BUTTON_2,
    COLOUR_WIDGET_GRADIENT_1,
    COLOUR_WIDGET_GRADIENT_2,

    COLOUR_SCROLLBAR_BACKGROUND,
    COLOUR_SCROLLBAR_CONTROL,

    COLOUR_LIST_ITEM_1,
    COLOUR_LIST_ITEM_2,
    COLOUR_LIST_ITEM_SELECTED,
};

class UITheme
{
 protected:
    bool m_initialised;
    FontHandle* m_font;
    FontHandle* m_fontHighDPI;
    FontHandle* m_iconFont;
    FontHandle* m_iconFontHighDPI;
    FrontierApp* m_app;

 public:
    UITheme(FrontierApp* video);
    virtual ~UITheme();

    virtual bool init();

    virtual uint32_t getColour(ThemeColour colour);

    virtual void drawBackground(Geek::Gfx::Surface* surface);
    virtual void drawBorder(Geek::Gfx::Surface* surface, UIBorderType type, UIState state, int x, int y, int w, int h);

    virtual void drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, bool inverted = false);
    virtual int getTextWidth(std::wstring text);
    virtual int getTextHeight();

    virtual void drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted = false);
    virtual int getIconWidth(wchar_t icon);
    virtual int getIconHeight();

    FrontierApp* getApp() { return m_app; }
};

#define FRONTIER_ICON_FOLDER_OPEN 0xf07c
#define FRONTIER_ICON_CLOSE 0xf00d
#define FRONTIER_ICON_SAVE 0xf0c7
#define FRONTIER_ICON_SYNC 0xf021

};

#endif
