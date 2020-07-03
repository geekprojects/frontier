/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <frontier/frontier.h>
#include <frontier/widgets.h>
#include <frontier/contextmenu.h>

#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Widget::Widget(FrontierApp* ui, wstring widgetName) : Logger(L"Widget[" + widgetName + L"]")
{
    initWidget(ui, widgetName);
}

Widget::Widget(FrontierWindow* window, wstring widgetName) : Logger(L"Widget[" + widgetName + L"]")
{
    initWidget(window->getApp(), widgetName);
    m_window = window;
}

Widget::~Widget()
{
    for (Widget* child : m_children)
    {
        child->decRefCount();
        child->setParent(NULL);
    }
    m_children.clear();
}

void Widget::initWidget(FrontierApp* app, wstring widgetName)
{
    m_app = app;
    m_widgetName = widgetName;
    m_widgetNames.insert(widgetName);

    m_window = NULL;
    m_parent = NULL;
    m_privateData = NULL;
    m_contextMenu = NULL;

    m_dirty = DIRTY_SIZE | DIRTY_CONTENT;

    m_minSize = Size(0, 0);
    m_maxSize = Size(0, 0);
    m_setSize = Size(0, 0);

    m_styleTimestamp = 0;
    m_cachedBoxModelTimestamp = 0;
    m_cachedTextFont = NULL;
    m_cachedTextFontTimestamp = 0;

    //m_mouseOver = false;
    m_selected = false;

    m_initialised = false;

    if (m_app != NULL)
    {
        m_app->registerObject(this);
    }

#if FRONTIER_ENGINE_COCOA
    m_widgetClasses.insert(L"MacOS");
#endif
}

void Widget::init()
{
}

void Widget::calculateSize()
{
}

void Widget::layout()
{
}

void Widget::setPosition(int x, int y)
{
    if (m_position.x != x || m_position.y != y)
    {
        // We will need to redraw the new position!
        setDirty(DIRTY_CONTENT | DIRTY_SIZE, true);
        m_position.x = x;
        m_position.y = y;
    }
}

Size Widget::setSize(Size size)
{
    // Clip the specified size to our min/max
    size.setMax(m_minSize);
    size.setMin(m_maxSize);

    if (size != m_setSize)
    {
        setDirty(DIRTY_SIZE);
        m_setSize = size;
    }

    return size;
}

bool Widget::draw(Geek::Gfx::Surface* surface, Rect visible)
{
    return draw(surface);
}

bool Widget::draw(Geek::Gfx::Surface* surface)
{
    return true;
}

void Widget::callInit()
{
    if (!m_initialised)
    {
        m_initialised = true;
        init();
    }
}

Size Widget::getBorderSize()
{
    BoxModel boxModel = getBoxModel();

    return Size(boxModel.getLeft() + boxModel.getRight(), boxModel.getTop() + boxModel.getBottom());
}

bool Widget::drawBorder(Surface* surface)
{
    auto props = getStyleProperties();
    BoxModel boxModel = getBoxModel(props);

    int borderRadius = 0;
    if (hasStyle("border-radius", props))
    {
        borderRadius = getStyle("border-radius", props);
    }

    int surfaceWidth = surface->getWidth();
    int surfaceHeight = surface->getHeight();

    if (borderRadius < 0 || (borderRadius > 0 && ((int)surfaceWidth < borderRadius * 2 || (int)surfaceHeight < borderRadius * 2)))
    {
        borderRadius = 0;
    }

    int borderX = boxModel.marginLeft;
    int borderY = boxModel.marginTop;
    int borderWidth = surfaceWidth - (boxModel.marginLeft + boxModel.marginRight);
    int borderHeight = surfaceHeight - (boxModel.marginTop + boxModel.marginBottom);

    uint64_t backgroundColour = getStyle("background-color", props);
    if (backgroundColour != FRONTIER_COLOUR_TRANSPARENT)
    {
        if (hasStyle("background-image", props))
        {
            // We only support basic linear gradients for now
            uint64_t backgroundColour = getStyle("background-image", props);
            uint32_t g1 = backgroundColour >> 32;
            uint32_t g2 = backgroundColour & 0xffffffff;

            if (borderRadius > 0)
            {
                surface->drawGradRounded(borderX, borderY, borderWidth, borderHeight, borderRadius, g1, g2);
            }
            else
            {
                surface->drawGrad(borderX, borderY, borderWidth, borderHeight, g1, g2);
            }
        }
        else if (hasStyle("background-color", props))
        {
            if (borderRadius > 0)
            {
                surface->drawRectFilledRounded(borderX, borderY, borderWidth, borderHeight, borderRadius, backgroundColour);
            }
            else
            {
                surface->drawRectFilled(borderX, borderY, borderWidth, borderHeight, backgroundColour);
            }
        }
    }

    // Top
    if (boxModel.borderTopWidth > 0)
    {
        uint32_t borderColour = getStyle("border-top-color", props);
        surface->drawLine(borderX, borderY, borderX + borderWidth - (borderRadius), borderY, 0xff000000 | borderColour);
    }

    // Right
    if (boxModel.borderRightWidth > 0)
    {
        uint32_t borderColour = getStyle("border-right-color", props);
        surface->drawLine(borderX + borderWidth, borderY + borderRadius, borderX + borderWidth, borderY + borderHeight - (borderRadius), 0xff000000 | borderColour);
    }

    // Bottom
    if (boxModel.borderBottomWidth > 0)
    {
        uint32_t borderColour = getStyle("border-bottom-color", props);
        surface->drawLine(borderX + borderRadius, borderY + borderHeight , borderX + borderWidth - (borderRadius),  borderY + borderHeight , 0xff000000 | borderColour);
    }

    // Left
    if (boxModel.borderLeftWidth > 0)
    {
        uint32_t borderColour = getStyle("border-left-color", props);
        surface->drawLine(borderX, borderY + borderRadius, borderX, borderY + borderHeight - (borderRadius), 0xff000000 | borderColour);
    }

    if (borderRadius > 0)
    {
        if (boxModel.borderTopWidth > 0 && boxModel.borderRightWidth > 0)
        {
            uint32_t borderColour = 0xff000000 | getStyle("border-top-color", props);
            surface->drawCorner(borderX + borderWidth, borderY, TOP_RIGHT, borderRadius, borderColour);
        }
        if (boxModel.borderBottomWidth > 0 && boxModel.borderRightWidth > 0)
        {
            uint32_t borderColour = 0xff000000 | getStyle("border-bottom-color", props);
            surface->drawCorner(borderX + borderWidth, borderY + borderHeight, BOTTOM_RIGHT, borderRadius, borderColour);
        }

        if (boxModel.borderBottomWidth > 0 && boxModel.borderLeftWidth > 0)
        {
            uint32_t borderColour = 0xff000000 | getStyle("border-bottom-color", props);
            surface->drawCorner(borderX, borderY + borderHeight, BOTTOM_LEFT, borderRadius, borderColour);
        }

        if (boxModel.borderBottomWidth > 0 && boxModel.borderLeftWidth > 0)
        {
            uint32_t borderColour = 0xff000000 | getStyle("border-top-color", props);
            surface->drawCorner(borderX, borderY, TOP_LEFT, borderRadius, borderColour);
        }
    }

    return true;
}

bool Widget::hasStyle(string style)
{
    auto props = getStyleProperties();
    return hasStyle(style, props);
}

bool Widget::hasStyle(string style, unordered_map<string, int64_t>& properties)
{
    return (properties.find(style) != properties.end());
}

int64_t Widget::getStyle(string style)
{
    auto props = getStyleProperties();
    return getStyle(style, props);
}

int64_t Widget::getStyle(std::string style, unordered_map<string, int64_t>& properties)
{
    auto it = properties.find(style);
    if (it != properties.end())
    {
        return it->second;
    }
    return (uint64_t)-1ll;
}


void Widget::setStyle(string style, int64_t value)
{
    m_widgetStyleProperties.setProperty(style, value);
    setDirty(DIRTY_STYLE);
}

unordered_map<string, int64_t>& Widget::getStyleProperties()
{
    uint64_t styleTS = m_app->getStyleEngine()->getTimestamp();
    if ((m_dirty & DIRTY_STYLE) || styleTS != m_styleTimestamp)
    {
        m_styleTimestamp = styleTS;
        m_cachedStyleProperties = m_app->getStyleEngine()->getProperties(this);

    }

    return m_cachedStyleProperties;
}

BoxModel& Widget::getBoxModel()
{
    uint64_t styleTS = m_app->getStyleEngine()->getTimestamp();
    if ((m_dirty & DIRTY_STYLE) || styleTS != m_cachedBoxModelTimestamp)
    {
        auto props = getStyleProperties();
        return getBoxModel(props);
    }

    return m_cachedBoxModel;
}

BoxModel& Widget::getBoxModel(std::unordered_map<std::string, int64_t>& props)
{
    uint64_t styleTS = m_app->getStyleEngine()->getTimestamp();
    if ((m_dirty & DIRTY_STYLE) || styleTS != m_cachedBoxModelTimestamp)
    {
        m_cachedBoxModel.marginTop = getStyle("margin-top", props);
        m_cachedBoxModel.marginRight = getStyle("margin-right", props);
        m_cachedBoxModel.marginBottom = getStyle("margin-bottom", props);
        m_cachedBoxModel.marginLeft = getStyle("margin-left", props);

        m_cachedBoxModel.paddingTop = getStyle("padding-top", props);
        m_cachedBoxModel.paddingRight = getStyle("padding-right", props);
        m_cachedBoxModel.paddingBottom = getStyle("padding-bottom", props);
        m_cachedBoxModel.paddingLeft = getStyle("padding-left", props);

        m_cachedBoxModel.borderTopWidth = getStyle("border-top-width", props);
        m_cachedBoxModel.borderRightWidth = getStyle("border-right-width", props);
        m_cachedBoxModel.borderBottomWidth = getStyle("border-bottom-width", props);
        m_cachedBoxModel.borderLeftWidth = getStyle("border-left-width", props);

        m_cachedBoxModelTimestamp = m_styleTimestamp;
    }

    return m_cachedBoxModel;
}

bool Widget::hasWidgetClass(std::wstring className)
{
    auto it = m_widgetClasses.find(className);
    return (it != m_widgetClasses.end());
}

void Widget::setWidgetClass(std::wstring className)
{
    m_widgetClasses.insert(className);
    setDirty(DIRTY_STYLE);
}

void Widget::clearWidgetClass(std::wstring className)
{
    auto it = m_widgetClasses.find(className);
    if (it != m_widgetClasses.end())
    {
        m_widgetClasses.erase(it);
        setDirty(DIRTY_STYLE);
    }
}

Geek::FontHandle* Widget::getTextFont()
{
    uint64_t styleTS = m_app->getStyleEngine()->getTimestamp();
    if (m_cachedTextFont == NULL || (m_dirty & DIRTY_STYLE) || styleTS != m_cachedTextFontTimestamp)
    {
        auto props = getStyleProperties();
        if (!hasStyle("font-family", props))
        {
            log(WARN, "getTextFont: No font-family specified");
            return NULL;
        }

        const char* fontFamily = (const char*)getStyle("font-family", props);
        const char* fontStyle = "Regular";

        if (hasStyle("font-style"))
        {
            fontStyle = (const char*)getStyle("font-style", props);
        }
        int fontSize = getStyle("font-size", props);
        if (m_cachedTextFont != NULL)
        {
            if (m_cachedTextFont->getFontFace()->getFamily()->getName() == string(fontFamily) &&
                m_cachedTextFont->getFontFace()->getStyle() == fontStyle &&
                m_cachedTextFont->getPointSize() == fontSize)
            {
                return m_cachedTextFont;
            }

            delete m_cachedTextFont;
        }

        FontManager* fm = m_app->getFontManager();
#if 0
        log(DEBUG, "getTextFont: Opening fontFamily: %s, style: %s fontSize: %d", fontFamily, fontStyle, fontSize);
#endif

        m_cachedTextFont = fm->openFont(fontFamily, fontStyle, fontSize);
        m_cachedTextFontTimestamp = m_app->getStyleEngine()->getTimestamp();
    }

    return m_cachedTextFont;
}

void Widget::drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, Geek::FontHandle* font)
{
    if (font == NULL)
    {
        font = getTextFont();
    }

    int colour = getStyle("text-color");
    font->write(surface, x, y, text, colour);
}

void Widget::setParent(Widget* widget)
{
    m_parent = widget;

    callInit();
}

Widget* Widget::findParent(const type_info& type)
{
    if (m_parent == NULL)
    {
        return NULL;
    }

    if (typeid(*m_parent).hash_code() == type.hash_code())
    {
        return m_parent;
    }
    return m_parent->findParent(type);;
}

FrontierWindow* Widget::getWindow()
{
    if (m_window != NULL)
    {
        return m_window;
    }

    if (m_parent != NULL)
    {
        m_window = m_parent->getWindow();
        return m_window;
    }

    return NULL;
}

Geek::Vector2D Widget::getAbsolutePosition() const
{
    Vector2D pos = m_position;

    if (m_parent != NULL)
    {
        pos += m_parent->getAbsolutePosition();
    }

    return pos;
}

bool Widget::intersects(int x, int y) const
{
    Vector2D thisPos = getAbsolutePosition();
    int x1 = thisPos.x;
    int y1 = thisPos.y;
    int x2 = x1 + getWidth();
    int y2 = y1 + getHeight();
    return (x >= x1 && y >= y1 && x < x2 && y < y2);
}

void Widget::setDirty()
{
    setDirty(DIRTY_SIZE | DIRTY_CONTENT | DIRTY_STYLE, false);
}

void Widget::setDirty(int dirty, bool children)
{
    callInit();
    m_dirty |= dirty;

    if (children)
    {
        for (Widget* child : getChildren())
        {
            child->setDirty(dirty, true);
        }
    }
    else
    {
        int parentDirty = dirty & ~DIRTY_STYLE; // Dirty flags doesn't propogate upwards
        if (m_parent != NULL && parentDirty != 0)
        {
            m_parent->setDirty(dirty);
        }
    }
}

void Widget::clearDirty()
{
    m_dirty = 0;

    for (Widget* child : m_children)
    {
        child->clearDirty();
    }
}

void Widget::setActive()
{
    getWindow()->setActiveWidget(this);
    setDirty(DIRTY_CONTENT | DIRTY_STYLE);
}

bool Widget::isActive()
{
    FrontierWindow* window = getWindow();
    if (window != NULL)
    {
        return (window->getActiveWidget() == this);
    }
    return false;
}

void Widget::activateNext(Widget* current)
{
    if (m_parent != NULL)
    {
        m_parent->activateNext(this);
    }
}

bool Widget::isVisible(Widget* child)
{
    if (m_parent != NULL)
    {
        return m_parent->isVisible(this);
    }

    return (getWindow() != NULL);
}

void Widget::openContextMenu()
{
    openContextMenu(getAbsolutePosition());
}

void Widget::openContextMenu(Geek::Vector2D pos)
{
    if (m_contextMenu == NULL)
    {
        return;
    }

    getWindow()->openContextMenu(pos, m_contextMenu);
}

Widget* Widget::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            if (mouseButtonEvent->direction)
            {
                if (mouseButtonEvent->doubleClick)
                {
                    m_doubleClickSignal.emit(this);
                }
                else
                {
                    m_clickSignal.emit(this);
                }
            }
            return this;
        }

        default:
            break;
    }
    return NULL;
}

void Widget::onMouseEnter()
{
    //m_mouseOver = true;
    m_mouseEnterSignal.emit(true);
    setDirty(DIRTY_CONTENT | DIRTY_STYLE);
}

void Widget::onMouseLeave()
{
    //m_mouseOver = false;
    m_mouseEnterSignal.emit(false);
    setDirty(DIRTY_CONTENT | DIRTY_STYLE);
}

bool Widget::isMouseOver()
{
    FrontierWindow* window = getWindow();
    if (window != NULL)
    {
        return window->getMouseOverWidget() == this;
    }
    return false;
}

void Widget::dump(int level)
{
    string spaces = "";
    int i;
    for (i = 0; i < level; i++)
    {
        spaces += "    ";
    }

    log(Geek::DEBUG, "%s%s(%p): x=%d, y=%d, size=%s", spaces.c_str(), m_widgetName.c_str(), this, m_position.x, m_position.y, m_setSize.toString().c_str());

    vector<Widget*>::iterator it;
    for (it = m_children.begin(); it != m_children.end(); it++)
    {
        (*it)->dump(level + 1);
    }
}

