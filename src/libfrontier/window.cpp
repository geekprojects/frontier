/*
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

    m_widget = NULL;
    m_dragWidget = NULL;
    m_mouseOverWidget = NULL;
    m_dragWidget = NULL;
    m_activeWidget = NULL;

    m_surface = NULL;

    m_size.set(640, 480);

    m_app->addWindow(this);
}

FrontierWindow::~FrontierWindow()
{
    if (m_widget != NULL)
    {
        m_widget->decRefCount();
    }

    if (m_activeWidget != NULL)
    {
        m_activeWidget->decRefCount();
    }

    if (m_mouseOverWidget != NULL)
    {
        m_mouseOverWidget->decRefCount();
    }

    if (m_dragWidget != NULL)
    {
        m_dragWidget->decRefCount();
    }

    if (m_surface != NULL)
    {
        delete m_surface;
    }
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

void FrontierWindow::setContent(Widget* content)
{
    if (m_widget != NULL)
    {
        m_widget->decRefCount();
    }

    m_widget = content;
    m_widget->incRefCount();
    m_widget->setWindow(this);
    m_widget->setPosition(0, 0);
    m_widget->setDirty();
}

void FrontierWindow::setActiveWidget(Widget* widget)
{
    if (m_activeWidget == widget)
    {
        return;
    }

    if (m_activeWidget != NULL)
    {
        m_activeWidget->signalInactive().emit();
        m_activeWidget->decRefCount();
    }

    m_activeWidget = widget;

    if (m_activeWidget != NULL)
    {
        log(DEBUG, "setActiveWidget: Active: %s (%p)", typeid(*widget).name(), widget);
        m_activeWidget->incRefCount();
        m_activeWidget->signalActive().emit();
    }
    else
    {
        log(DEBUG, "setActiveWidget: Active: %p", widget);
    }
}

void FrontierWindow::setDragWidget(Widget* widget)
{
    if (m_dragWidget != widget)
    {
        if (m_dragWidget != NULL)
        {
            m_dragWidget->decRefCount();
        }
        m_dragWidget = widget;
        if (m_dragWidget != NULL)
        {
            m_dragWidget->incRefCount();
        }
    }
    m_dragTime = m_app->getTimestamp();
}

void FrontierWindow::show()
{
    initInternal();

    m_engineWindow->show();
    if (!(m_flags & WINDOW_TOOL_TIP))
    {
        m_app->setActiveWindow(this);
    }

    m_widget->setDirty();
    update();
}

void FrontierWindow::hide()
{
    if (m_engineWindow != NULL)
    {
        m_engineWindow->hide();
    }
}

void FrontierWindow::setSize(Size size)
{
    m_size = size;
    if (m_widget != NULL)
    {
        m_widget->setDirty(DIRTY_SIZE, true);

        update();
    }
}

void FrontierWindow::update(bool force)
{
    initInternal();

    if (m_widget->isDirty(DIRTY_SIZE))
    {
        m_widget->calculateSize();

        Size min = m_widget->getMinSize();
        Size max = m_widget->getMaxSize();

        m_size.setMax(min);
        m_size.setMin(max);

        m_size = m_widget->setSize(m_size);

#if 0
        log(DEBUG, "update: min=%s, max=%s", min.toString().c_str(), max.toString().c_str());
        log(DEBUG, "update: Updating window size: %s", m_size.toString().c_str());
#endif

        m_widget->layout();

        // Make sure we redraw
        m_widget->setDirty(DIRTY_CONTENT);

        // Likely to be different?
        //m_mouseOverWidget = NULL;
        //updateCursor();
    }

#if 0
    m_widget->dump(1);
#endif

    float scale = m_engineWindow->getScaleFactor();

    if (m_surface == NULL || (int)m_surface->getWidth() != m_size.width || (int)m_surface->getHeight() != m_size.height)
    {
        if (m_surface != NULL)
        {
            delete m_surface;
        }

        if (scale > 1.0)
        {
            m_surface = new HighDPISurface(m_size.width, m_size.height, 4);
        }
        else
        {
            m_surface = new Surface(m_size.width, m_size.height, 4);
        }

        m_widget->setDirty(DIRTY_CONTENT);
    }
#if 0
    log(DEBUG, "update: Window surface=%p", m_surface);
#endif

    if (m_widget->isDirty() || force)
    {
        m_app->getTheme()->drawBackground(m_surface);

        m_widget->draw(m_surface);

        m_engineWindow->update();

    }
    m_widget->clearDirty();

}

void FrontierWindow::updateCursor()
{
    if (m_engineWindow == NULL)
    {
        return;
    }

    WindowCursor cursor = CURSOR_POINTER;
    if (m_mouseOverWidget != NULL)
    {
        cursor = m_mouseOverWidget->getCursor();
    }

    if (cursor != m_currentCursor)
    {
        m_engineWindow->resetCursor();

        log(DEBUG, "updateCursor: Updating cursor: %u", cursor);
        if (cursor != CURSOR_POINTER && m_mouseOverWidget != NULL)
        {
            Vector2D pos = m_mouseOverWidget->getAbsolutePosition();
            Size size = m_mouseOverWidget->getSize();
            log(DEBUG, "updateCursor: Rect: %d,%d, w=%d, h=%d", pos.x, pos.y, size.width, size.height);
            m_engineWindow->updateCursor(cursor, pos.x, pos.y, size.width, size.height);
        }

        m_currentCursor = cursor;
    }
}

/*
int FrontierWindow::getWidth()
{
    if (m_widget != NULL)
    {
        return m_widget->getWidth();
    }
    return 0;
}

int FrontierWindow::getHeight()
{
    if (m_widget != NULL)
    {
        return m_widget->getHeight();
    }
    return 0;
}
*/

void FrontierWindow::openContextMenu(Geek::Vector2D pos, Menu* menu)
{
    ContextMenu* cm = m_app->getContextMenuWindow();
    cm->setMenu(menu);

    cm->setSize(Size(0, 0));
    cm->show();

    Vector2D screenPos = getScreenPosition(pos);
    cm->setPosition(screenPos);
}

void FrontierWindow::postMessage(Message* message)
{
}

bool FrontierWindow::handleMessage(Message* message)
{
    Widget* prevActiveWidget = m_activeWidget;
    Widget* destWidget = NULL;
    bool updateActive = false;

    if (message->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)message;
        imsg->window = this;

        switch (imsg->inputMessageType)
        {
            case FRONTIER_MSG_INPUT_MOUSE_BUTTON:
                m_app->setActiveWindow(this);
                // Fall through
            case FRONTIER_MSG_INPUT_MOUSE_WHEEL:
                updateActive = true;
                destWidget = m_widget->handleMessage(message);
               break;

            case FRONTIER_MSG_INPUT_MOUSE_MOTION:
                destWidget = m_widget->handleMessage(message);

                if (m_mouseOverWidget != destWidget)
                {
                    if (m_mouseOverWidget != NULL)
                    {
                        m_mouseOverWidget->onMouseLeave();
                        m_mouseOverWidget->decRefCount();
                    }

                    m_mouseOverWidget = destWidget;

                    if (m_mouseOverWidget != NULL)
                    {
                        m_mouseOverWidget->incRefCount();
                        m_mouseOverWidget->onMouseEnter();
                    }

                }
                updateCursor();

                break;

            case FRONTIER_MSG_INPUT_KEY:
                if (m_activeWidget != NULL)
                {
                    destWidget = m_activeWidget->handleMessage(message);
                }
                break;
        }

        if (m_dragWidget != NULL)
        {
            uint64_t now = m_app->getTimestamp();
            uint64_t diff = now - m_dragTime;
            if (diff >= 100)
            {
                destWidget = m_dragWidget->handleMessage(message);
                m_dragTime = m_app->getTimestamp();
            }
        }
    }



    bool updateRequired = m_widget->isDirty();
    if (destWidget != NULL || updateRequired || updateActive)
    {
        if (updateActive &&
            destWidget != NULL &&
            prevActiveWidget == m_activeWidget && // Make sure it hasn't been explicitly set
            prevActiveWidget != destWidget)
        {
            setActiveWidget(destWidget);
            updateRequired = true;
        }

        if (updateRequired)
        {
            update();
        }
    }

    delete message;

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

