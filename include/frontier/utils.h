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

#ifndef __FRONTIER_UTILS_H_
#define __FRONTIER_UTILS_H_

#include <string>

namespace Frontier {

struct Size
{
    int width;
    int height;

    Size()
    {
        width = 0;
        height = 0;
    }

    Size(int _w, int _h)
    {
        width = _w;
        height = _h;
    }

    void set(int _w, int _h)
    {
        width = _w;
        height = _h;
    }

    std::string toString()
    {
        char buffer[32];
        snprintf(buffer, 32, "%d,%d", width, height);
        return std::string(buffer);
    }

    void setMin(Size& other)
    {
        setMinWidth(other);
        setMinHeight(other);
    }

    void setMax(Size& other)
    {
        setMaxWidth(other);
        setMaxHeight(other);
    }

    void setMinWidth(Size& other)
    {
        if (other.width < width)
        {
            width = other.width;
        }
    }

    void setMaxWidth(Size& other)
    {
        if (other.width > width)
        {
            width = other.width;
        }
    }

    void setMinHeight(Size& other)
    {
        if (other.height < height)
        {
            height = other.height;
        }
    }

    void setMaxHeight(Size& other)
    {
        if (other.height > height)
        {
            height = other.height;
        }
    }

    int get(bool isHoriz)
    {
        if (isHoriz)
        {
            return width;
        }
        else
        {
            return height;
        }
    }
};

class Utils
{
 public:
    static std::wstring string2wstring(std::string str);
    static std::string wstring2string(std::wstring str);
};

};

#endif
