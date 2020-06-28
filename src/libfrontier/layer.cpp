/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2020 Ian Parker <ian@geekprojects.com>
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


#include <frontier/layer.h>
#include <frontier/widgets.h>

using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Layer::Layer(FrontierApp* app, bool primary) : Logger(L"Layer")
{
    m_app = app;
    m_primary = primary;

    m_window = NULL;
    m_root = NULL;
    m_surface = NULL;

    m_horizontalAlign = ALIGN_CENTER;
    m_verticalAlign = ALIGN_MIDDLE;

    m_app->registerObject(this);
}

Layer::~Layer()
{
    if (m_root != NULL)
    {
        m_root->decRefCount();
    }

    if (m_surface != NULL)
    {
        delete m_surface;
    }
}

void Layer::setModal(bool modal)
{
    m_modal = modal;
    if (m_root != NULL)
    {
        m_root->setDirty(DIRTY_CONTENT);
    }
}

void Layer::setWindow(FrontierWindow* window)
{
    m_window = window;
}

void Layer::setContentRoot(Widget* root)
{
    if (m_root != NULL)
    {
        m_root->decRefCount();
    }

    m_root = root;
    m_root->setDirty();
    m_root->incRefCount();
}

bool Layer::update()
{
    float scale = m_window->getScaleFactor();

    if (m_root->isDirty(DIRTY_SIZE) || m_root->isDirty(DIRTY_STYLE))
    {
        m_root->calculateSize();

        Size min = m_root->getMinSize();
        if (m_primary)
        {
            Size max = m_root->getMaxSize();

            Size size = m_rect.getSize();
            size.setMax(min);
            size.setMin(max);

            if (!m_window->isFullScreen())
            {
                size = m_root->setSize(size);
                m_rect.width = size.width;
                m_rect.height = size.height;
            }
            else
            {
                m_root->setSize(size);
            }
        }
        else
        {
            m_root->setSize(min);
            m_rect.width = min.width;
            m_rect.height = min.height;
        }

#if 0
        log(DEBUG, "update: min=%s, max=%s", min.toString().c_str(), max.toString().c_str());
        log(DEBUG, "update: Updating window size: %s", m_size.toString().c_str());
#endif

        m_root->setPosition(0, 0);

        // Make sure we redraw
        m_root->setDirty(DIRTY_CONTENT);

        //updateCursor();
    }

    Surface* surface = Surface::updateSurface(m_surface, m_rect.width, m_rect.height, scale);
    if (surface != m_surface)
    {
        m_surface = surface;
        m_root->setDirty(DIRTY_SIZE | DIRTY_CONTENT, true);
    }

    if (m_root->isDirty())
    {
        m_root->layout();

        m_root->draw(m_surface);
        m_root->clearDirty();

        return true;
    }
    else
    {
        return false;
    }
}

