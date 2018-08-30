#ifndef __FRONTIER_UTILS_H_
#define __FRONTIER_UTILS_H_

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
        sprintf(buffer, "%d,%d", width, height);
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

};

#endif
