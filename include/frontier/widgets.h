#ifndef __FRONTIER_WIDGETS_H_
#define __FRONTIER_WIDGETS_H_

#include <vector>

#include <frontier/frontier.h>

class Widget
{
 protected:
    FrontierApp* m_ui;
    Widget* m_parent;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    bool m_dirty;

    int m_minWidth;
    int m_minHeight;
    int m_margin;
    int m_padding;

 public:
    Widget(FrontierApp* ui);
    virtual ~Widget();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    int getX() { return m_x; }
    int getY() { return m_y; }
    void setPosition(int x, int y) { m_x = x; m_y = y; }
    virtual void setWidth(int width) { m_width = width; }
    virtual void setHeight(int height) { m_height = height; }
    virtual int getWidth() { return m_width; }
    virtual int getHeight() { return m_height; }
    virtual void setMinWidth(int width) { m_minWidth = width; }
    virtual void setMinHeight(int height) { m_minHeight = height; }
    void setParent(Widget* w) { m_parent = w; }
    Widget* getParent() { return m_parent; }

    Geek::Vector2D getAbsolutePosition();
    bool intersects(int x, int y);

    void setDirty();
    bool isDirty() { return m_dirty; }

    virtual Widget* handleMessage(Message* msg);
};

class Frame : public Widget
{
 private:
    bool m_horizontal;
    bool m_border;
    std::vector<Widget*> m_children;

    virtual void calculateSize();

 public:
    Frame(FrontierApp* ui, bool horizontal);
    virtual ~Frame();

    virtual void setWidth(int width);
    virtual void setHeight(int height);

    void setBorder(bool border) { m_border = border; }

    void add(Widget* widget);

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);
};

class Grid : Widget
{
 private:

 public:
    Grid(FrontierApp* ui);
    virtual ~Grid();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);
};

class Button : public Widget
{
 protected:
    std::wstring m_text;
    bool m_state;

 public:
    Button(FrontierApp* ui, std::wstring text);
    ~Button();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);
};

class IconButton : public Button
{
 private:
    wchar_t m_icon;

 public:
    IconButton(FrontierApp* ui, wchar_t icon);
    ~IconButton();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};


class Label : public Widget
{
 private:
    std::wstring m_text;
    int m_lineHeight;

 public:
    Label(FrontierApp* ui, std::wstring text);
    ~Label();

    void setText(std::wstring wtext);

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);
};

struct ListItem
{
    virtual std::wstring getText() { return L""; }
};

struct TextListItem : public ListItem
{
    std::wstring m_text;
    std::wstring getText() { return m_text; }

    TextListItem() {}
    TextListItem(std::wstring text) { m_text = text; }
};

class List : public Widget
{
 private:
    std::vector<ListItem*> m_list;
    int m_selected;
    int m_itemHeight;

 public:
    List(FrontierApp* ui);
    ~List();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);

    void clearItems();
    void addItem(ListItem* item);
    int getSelected() { return m_selected; }
    ListItem* getItem(int i) { return m_list.at(i); }
};

class ScrollBar : public Widget
{
 private:
    int m_min;
    int m_max;
    int m_pos;
    int m_size;
    int m_preferredLength;
    bool m_dragging;

    int getControlPos();
    int getControlSize();
    int range() { return m_max - (m_min + m_size); }

 public:
    ScrollBar(FrontierApp* ui);
    ~ScrollBar();

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);

    void set(int min, int max, int size);
    void setPos(int pos);
    int getPos();
};

class Scroller : public Widget
{
 private:
    int m_preferredHeight;

    ScrollBar* m_scrollBar;
    Widget* m_child;
    Geek::Gfx::Surface* m_childSurface;

    void checkSurfaceSize();
    int getWidthOverhead() { return (m_scrollBar->getWidth() - 2); }

 public:
    Scroller(FrontierApp* ui);
    Scroller(FrontierApp* ui, Widget* child);
    ~Scroller();

    virtual void calculateSize();
    virtual void setWidth(int width);
    int getPos() { return m_scrollBar->getPos(); }

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleMessage(Message* msg);

    void setChild(Widget* child);
};

#define FRONTIER_MSG_UI_BUTTON_PRESSED 0x1000
#define FRONTIER_MSG_UI_LIST_SELECTED 0x2000

#endif
