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

#ifndef __FRONTIER_TYPES_H_
#define __FRONTIER_TYPES_H_

/**
 * \brief Specifies how to align text and objects horizontally
 */
enum HorizontalAlign
{
    ALIGN_LEFT, ///< Align left
    ALIGN_CENTER, ///< Align centrally
    ALIGN_RIGHT ///< Align right
};

/**
 * \brief Specifies how to align text and objects vertically
 */
enum VerticalAlign
{
    ALIGN_TOP, ///< Align top
    ALIGN_MIDDLE, ///< Align middle vertically
    ALIGN_BOTTOM ///< Align bottom
};

/**
 * \enum Frontier::DirtyFlag
 * \brief Describes what aspects of a widget are "dirty"
 */
enum DirtyFlag
{
    DIRTY_SIZE = 0x1,   ///< The size of the widget or its children have changed
    DIRTY_CONTENT = 0x2, ///< Just the contents of the widget needs redrawing
    DIRTY_STYLE = 0x4, ///< States on which style rules may apply have changed

    DIRTY_ALL = 0xff ///< All aspects of the widget are dirty
};

#endif
