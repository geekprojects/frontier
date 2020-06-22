/*
 *
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
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
#include <frontier/engine.h>
#include <frontier/widgets.h>
#include <frontier/contextmenu.h>
#include <frontier/widgets/frame.h>

#include <algorithm>
#include <typeinfo>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

FrontierWindow::FrontierWindow(FrontierApp* app, std::wstring title, int flags) : Logger(L"Window[" + title + L"]")
{
    m_app = app;
    m_engineWindow = NULL;
    m_initialised = false;

    m_title = title;
    m_flags = flags;
    m_visible = false;
    m_currentCursor = CURSOR_ARROW;

    m_content = NULL;
    m_mouseOverWidget = NULL;
    m_motionWidget = NULL;
    m_activeWidget = NULL;
    m_dragWidget = NULL;
    m_dragSurface = NULL;

    m_updateTimestamp = 0;
    m_drawMutex = Geek::Thread::createMutex();
    m_updating = false;
    m_windowSurface = NULL;

    m_menuBar = NULL;
    m_menu = NULL;

    m_rootLayer = new Layer(app, true);
    m_rootLayer->incRefCount();
    m_rootLayer->setSize(Size(640, 480));
    m_rootLayer->setWindow(this);
    Frame* rootFrame = new Frame(app, false);
    m_rootLayer->setContentRoot(rootFrame);
    m_layers.push_back(m_rootLayer);
    rootFrame->setWidgetClass(L"root");

    if (hasBorder() && !m_app->getEngine()->providesMenus())
    {
        m_menuBar = new MenuList(m_app, NULL, true);
        rootFrame->add(m_menuBar);
    }

    m_app->addWindow(this);
}

FrontierWindow::~FrontierWindow()
{
    for (Layer* layer : m_layers)
    {
        layer->decRefCount();
    }

    if (m_content != NULL)
    {
        m_content->decRefCount();
    }

    if (m_activeWidget != NULL)
    {
        m_activeWidget->decRefCount();
    }

    if (m_mouseOverWidget != NULL)
    {
        m_mouseOverWidget->decRefCount();
        m_mouseOverWidget = NULL;
    }

    if (m_motionWidget != NULL)
    {
        m_motionWidget->decRefCount();
        m_motionWidget = NULL;
    }

    delete m_engineWindow;
}

bool FrontierWindow::initInternal()
{
    if (!m_initialised)
    {
        bool res;
        res = m_app->getEngine()->initWindow(this);
        if (!res)
        {
            return false;
        }

        res = init();
        m_initialised = true;
        return res;
    }

    return true;
}

bool FrontierWindow::init()
{
    return true;
}

void FrontierWindow::setPosition(Geek::Vector2D position)
{
    m_engineWindow->setPosition(position.x, position.y);
}

Geek::Vector2D FrontierWindow::getPosition()
{
    return m_engineWindow->getPosition();
}

Frontier::Rect FrontierWindow::getRect()
{
    Vector2D pos = getPosition();
    return Rect(pos.x, pos.y, m_rootLayer->getRect().width, m_rootLayer->getRect().height);
}

void FrontierWindow::setContent(Widget* content)
{
    m_drawMutex->lock();

    Frame* rootFrame = (Frame*)m_rootLayer->getContentRoot();
    if (m_content != NULL)
    {
        rootFrame->remove(m_content);
        m_content->decRefCount();
    }

    m_content = content;
    m_content->incRefCount();
    m_content->setWindow(this);
    m_content->setPosition(0, 0);

    rootFrame->add(m_content);
    rootFrame->setDirty(DIRTY_ALL, true);

    m_drawMutex->unlock();
}

void FrontierWindow::setActiveWidget(Widget* widget)
{
    if (m_activeWidget == widget)
    {
        return;
    }

    if (m_activeWidget != NULL)
    {
        m_activeWidget->setDirty(DIRTY_STYLE);
        m_activeWidget->signalInactive().emit();
        m_activeWidget->decRefCount();
    }

    m_activeWidget = widget;

    if (m_activeWidget != NULL)
    {
        log(DEBUG, "setActiveWidget: Active: %s (%p)", typeid(*widget).name(), widget);
        m_activeWidget->incRefCount();
        m_activeWidget->setDirty(DIRTY_STYLE);
        m_activeWidget->signalActive().emit();
    }
    else
    {
        log(DEBUG, "setActiveWidget: Active: %p", widget);
    }
}

void FrontierWindow::setMotionWidget(Widget* widget)
{
    if (m_motionWidget != widget)
    {
        if (m_motionWidget != NULL)
        {
            m_motionWidget->decRefCount();
        }
        m_motionWidget = widget;
        if (m_motionWidget != NULL)
        {
            m_motionWidget->incRefCount();
        }
    }
    m_motionTime = m_app->getTimestamp();
}

void FrontierWindow::setMouseOver(Widget* widget)
{
    if (m_mouseOverWidget != widget)
    {
        if (widget != NULL)
        {
            widget->incRefCount();
        }

        if (m_mouseOverWidget != NULL)
        {
            m_mouseOverWidget->onMouseLeave();
            m_mouseOverWidget->decRefCount();
            m_mouseOverWidget->setDirty(DIRTY_CONTENT | DIRTY_STYLE);
        }

        m_mouseOverWidget = widget;
        if (m_mouseOverWidget != NULL)
        {
            m_mouseOverWidget->onMouseEnter();
            m_mouseOverWidget->setDirty(DIRTY_CONTENT | DIRTY_STYLE);
        }
    }
}

void FrontierWindow::dragWidget(Widget* widget)
{
    m_dragWidget = widget;
    m_dragWidget->incRefCount();

    if (widget == NULL)
    {
        return;
    }

    if (m_dragSurface != NULL)
    {
        delete m_dragSurface;
    }

    Size size = m_dragWidget->getSize();

    float scale = m_engineWindow->getScaleFactor();
    if (scale > 1.0)
    {
        m_dragSurface = new HighDPISurface(size.width, size.height, 4);
    }
    else
    {
        m_dragSurface = new Surface(size.width, size.height, 4);
    }

    m_dragWidget->draw(m_dragSurface);
}

Widget* FrontierWindow::dragOver(Vector2D position, Widget* current, bool dropped)
{
    log(DEBUG, "dragOver: position=%d,%d, current=%ls", position.x, position.y, current->getWidgetName().c_str());

    bool stop = false;
    if (dropped)
    {
        stop = current->dragDropSignal().emit(m_dragWidget, position);
    }
    else
    {
        stop = current->dragOverSignal().emit(m_dragWidget, position);
    }

    if (stop)
    {
        return current;
    }

    vector<Widget*> children = current->getChildren();
    for (Widget* child : children)
    {

        if (child->intersects(position.x, position.y))
        {
            Widget* accepted = dragOver(position, child, dropped);
            if (accepted != NULL)
            {
                return accepted;
            }
        }
    }
    return NULL;
}

void FrontierWindow::show()
{
    initInternal();

    m_engineWindow->show();
    if (!(m_flags & WINDOW_TOOL_TIP))
    {
        m_app->setActiveWindow(this);
    }

    m_visible = true;

    m_showSignal.emit();

    for (Layer* layer : m_layers)
    {
        layer->getContentRoot()->setDirty();
    }

    update();
}

void FrontierWindow::hide()
{
    m_visible = false;

    if (m_engineWindow != NULL)
    {
        m_engineWindow->hide();
    }
}

void FrontierWindow::setSize(Size size)
{
    if (size != m_rootLayer->getRect().getSize())
    {
        m_rootLayer->setSize(size);
        m_rootLayer->getContentRoot()->setDirty(DIRTY_ALL, true);

        requestUpdate();
    }
}

float FrontierWindow::getScaleFactor()
{
    if (m_engineWindow != NULL)
    {
        return m_engineWindow->getScaleFactor();
    }
    return 1.0;
}

void FrontierWindow::update(bool force)
{
    if (!m_visible)
    {
        return;
    }

    if (m_updating)
    {
        return;
    }
    m_updating = true;

    uint64_t now = m_app->getTimestamp();
    if (force)
    {
        if ((now - m_updateTimestamp) < 10)
        {
            log(INFO, "update: Rate limiting forced updates!");
            force = false;
        }
    }
    m_updateTimestamp = now;

    initInternal();

    if (m_menu == NULL)
    {
        if (hasBorder() && !m_app->getEngine()->providesMenus())
        {
            Menu* appMenu = m_app->getAppMenu();
            if (appMenu != NULL)
            {
                setMenu(appMenu);
            }
        }
    }

    m_drawMutex->lock();

    bool updated = false;
    for (Layer* layer : m_layers)
    {
        updated |= layer->update();
    }

    if (updated || force)
    {
        Surface* surface = Surface::updateSurface(
            m_windowSurface,
            m_rootLayer->getRect().width,
            m_rootLayer->getRect().height,
            getScaleFactor());

        if (surface != NULL)
        {
            m_windowSurface = surface;
        }

        Rect rootRect = m_rootLayer->getRect();
        for (Layer* layer : m_layers)
        {
            Rect layerRect = layer->getRect();
            switch (layer->getHorizontalAlign())
            {
                case ALIGN_LEFT:
                    layerRect.x = 0;
                    break;
                case ALIGN_CENTER:
                    layerRect.x = (rootRect.width / 2) - (layerRect.width / 2);
                    break;
                case ALIGN_RIGHT:
                    layerRect.x = rootRect.width - layerRect.width;
                    break;
            }

            switch (layer->getVerticalAlign())
            {
                case ALIGN_TOP:
                    layerRect.y = 0;
                    break;
                case ALIGN_MIDDLE:
                    layerRect.y = (rootRect.height / 2) - (layerRect.height / 2);
                    break;
                case ALIGN_BOTTOM:
                    layerRect.y = rootRect.height - layerRect.height;
                    break;
            }
            layer->setRect(layerRect);

            if (layer->isModal())
            {
                m_windowSurface->darken();
            }

            m_windowSurface->blit(layerRect.x, layerRect.y, layer->getSurface(), false);
        }

        m_engineWindow->update();
    }

    if (m_dragSurface != NULL)
    {
        m_windowSurface->blit(m_dragPosition.x, m_dragPosition.y, m_dragSurface);
    }

    m_updating = false;
    m_drawMutex->unlock();

}

void FrontierWindow::requestUpdate()
{
    if (m_engineWindow != NULL)
    {
        m_engineWindow->requestUpdate();
    }
}

void FrontierWindow::updateCursor()
{
    if (m_engineWindow == NULL)
    {
        return;
    }

    WindowCursor cursor = CURSOR_ARROW;
    if (m_mouseOverWidget != NULL)
    {
        cursor = m_mouseOverWidget->getCursor();
    }

    if (cursor != m_currentCursor)
    {
        m_engineWindow->resetCursor();

        log(DEBUG, "updateCursor: Updating cursor: %u", cursor);
        if (cursor != CURSOR_ARROW && m_mouseOverWidget != NULL)
        {
            Vector2D pos = m_mouseOverWidget->getAbsolutePosition();
            Size size = m_mouseOverWidget->getSize();
            log(DEBUG, "updateCursor: Rect: %d,%d, w=%d, h=%d", pos.x, pos.y, size.width, size.height);
            m_engineWindow->updateCursor(cursor, pos.x, pos.y, size.width, size.height);
        }

        m_currentCursor = cursor;
    }
}

void FrontierWindow::setMenu(Menu* menu)
{
    m_menu = menu;
    if (m_menuBar != NULL)
    {
        m_menuBar->setMenu(m_menu->getMenuItems());
    }
}

void FrontierWindow::openContextMenu(Geek::Vector2D pos, Menu* menu)
{
    ContextMenu* cm = m_app->getContextMenuWindow();
    cm->setMenu(menu);

    cm->setSize(Size(0, 0));
    cm->show();

    Vector2D screenPos = getScreenPosition(pos);
    cm->setPosition(screenPos);
}

void FrontierWindow::postEvent(Event* event)
{
}

bool FrontierWindow::handleEvent(Event* event)
{
    Widget* prevActiveWidget = m_activeWidget;
    Widget* destWidget = NULL;
    bool updateActive = false;
    bool forceUpdate = false;

    event->window = this;

    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseEvent = (MouseButtonEvent*)event;
            m_app->setActiveWindow(this);

            if (!mouseEvent->direction && m_dragWidget != NULL)
            {
                Widget* accepted = dragOver(m_dragPosition, m_rootLayer->getContentRoot(), true);
                if (accepted == NULL)
                {
                    // No one wanted this widget :(
                    m_dragWidget->dragCancelledSignal().emit(m_dragWidget);
                }

                m_dragWidget->decRefCount();
                m_dragWidget = NULL;
                if (m_dragSurface != NULL)
                {
                    m_dragSurface = NULL;
                    delete m_dragSurface;
                }
                forceUpdate = true;
            }
        } // Fall through
        case FRONTIER_EVENT_MOUSE_SCROLL:
        {
            MouseEvent* mouseEvent = (MouseEvent*)event;
            updateActive = true;
            int origX = mouseEvent->x;
            int origY = mouseEvent->y;
            vector<Layer*>::reverse_iterator rit;
            for (rit = m_layers.rbegin(); rit != m_layers.rend(); rit++)
            {
                Layer* layer = *rit;
                if (layer->getRect().intersects(origX, origY))
                {
                    mouseEvent->x = origX - layer->getRect().x;
                    mouseEvent->y = origY - layer->getRect().y;
                    destWidget = layer->getContentRoot()->handleEvent(event);
                    if (destWidget != NULL)
                    {
                        break;
                    }
                }
                if (layer->isModal())
                {
                    break;
                }
            }
            setMouseOver(destWidget);
        } break;

        case FRONTIER_EVENT_MOUSE_MOTION:
        {
            MouseEvent* mouseEvent = (MouseEvent*)event;
            int origX = mouseEvent->x;
            int origY = mouseEvent->y;

            vector<Layer*>::reverse_iterator rit;
            for (rit = m_layers.rbegin(); rit != m_layers.rend(); rit++)
            {
                Layer* layer = *rit;
                if (layer->getRect().intersects(origX, origY))
                {
                    mouseEvent->x = origX - layer->getRect().x;
                    mouseEvent->y = origY - layer->getRect().y;
                    destWidget = m_rootLayer->getContentRoot()->handleEvent(event);
                    if (destWidget != NULL)
                    {
                        break;
                    }
                }
                if (layer->isModal())
                {
                    break;
                }
            }

            setMouseOver(destWidget);
            if (m_dragSurface != NULL)
            {
                m_dragPosition.x = mouseEvent->x;
                m_dragPosition.y = mouseEvent->y;
                forceUpdate = true;
                dragOver(m_dragPosition, m_rootLayer->getContentRoot(), false);
            }

            updateCursor();
        } break;

        case FRONTIER_EVENT_KEY:
            if (m_activeWidget != NULL)
            {
                destWidget = m_activeWidget->handleEvent(event);
            }
            else
            {
                KeyEvent* keyEvent = (KeyEvent*)event;
                if (keyEvent->direction && keyEvent->key == KC_TAB)
                {
                    m_rootLayer->getContentRoot()->activateNext(NULL);
                }
            }
            break;
    }

    if (m_motionWidget != NULL)
    {
        uint64_t now = m_app->getTimestamp();
        uint64_t diff = now - m_motionTime;
        if (diff >= 10)
        {
            destWidget = m_motionWidget->handleEvent(event);
            m_motionTime = m_app->getTimestamp();
        }
    }

    bool updateRequired = m_rootLayer->getContentRoot()->isDirty();
    if (destWidget != NULL || updateRequired || updateActive || forceUpdate)
    {
        if (updateActive &&
            destWidget != NULL &&
            prevActiveWidget == m_activeWidget && // Make sure it hasn't been explicitly set
            prevActiveWidget != destWidget)
        {
            setActiveWidget(destWidget);
            updateRequired = true;
        }

        if (updateRequired || forceUpdate)
        {
            update();
        }
    }

    delete event;

    m_app->update();

    return true;
}

void FrontierWindow::gainedFocus()
{
    log(DEBUG, "gainedFocus: Here! this=%p", this);
}

void FrontierWindow::lostFocus()
{
    log(DEBUG, "lostFocus: Here! this=%p", this);
}

Vector2D FrontierWindow::getScreenPosition(Vector2D pos)
{
    Vector2D screenPos(0, 0);
    if (m_engineWindow == NULL)
    {
        return screenPos;
    }

    Vector2D windowPos = m_engineWindow->getPosition();

    screenPos = windowPos;
    screenPos += pos;

    return screenPos;
}

void FrontierWindow::addLayer(Layer* layer)
{
    m_layers.push_back(layer);
    layer->setWindow(this);
    layer->incRefCount();

    Widget* root = layer->getContentRoot();
    root->setDirty();
    root->setWidgetClass(L"root");
    m_rootLayer->getContentRoot()->setDirty(DIRTY_CONTENT);

    requestUpdate();
}

void FrontierWindow::removeLayer(Layer* layer)
{
    vector<Layer*>::iterator it = find(m_layers.begin(), m_layers.end(), layer);
    if (it == m_layers.end())
    {
        return;
    }

    m_layers.erase(it);

    m_rootLayer->getContentRoot()->setDirty(DIRTY_CONTENT);

    requestUpdate();
}

