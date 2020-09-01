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


#include <frontier/widgets/numberinput.h>
#include <geek/core-string.h>

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <limits.h>

using namespace Frontier;
using namespace Geek;
using namespace std;

FRONTIER_WIDGET(NumberInput, Frontier::NumberInput)

NumberInput::NumberInput(FrontierApp* app) : TextInput(app)
{
    init();
}

NumberInput::NumberInput(FrontierWindow* window) : TextInput(window)
{
    init();
}

NumberInput::~NumberInput()
{
}

void NumberInput::init()
{
    m_min = INT_MIN;
    m_max = INT_MAX;
    m_integerOnly = true;
}

void NumberInput::calculateSize()
{
    TextInput::calculateSize();
}

void NumberInput::setMin(double min)
{
    m_min = min;
}

void NumberInput::setMax(double max)
{
    m_max = max;
}

void NumberInput::setNumber(int i)
{
    wchar_t buf[100];
    swprintf(buf, 100, L"%d", i);
    setText(buf);
}

void NumberInput::setNumber(double d)
{
    wchar_t buf[100];
    swprintf(buf, 100, L"%f", d);
    setText(buf);
}


bool NumberInput::isValid(std::wstring wstr)
{
    string str = Utils::wstring2string(wstr);

    if (str.length() == 0)
    {
        return true;
    }

    const char* start = str.c_str();
    char* end;
    if (m_integerOnly)
    {
        int i = strtol(start, &end, 10);
        int e = errno;
        if (i == 0 && e != 0)
        {
            return false;
        }

        unsigned int len = end - start;
        if (wstr.length() != len)
        {
            return false;
        }
        return (i >= (int)m_min && i <= (int)m_max);
    }
    else
    {
        double d = strtod(start, &end);
        int e = errno;
        if (d == 0 && e != 0)
        {
            return false;
        }
        unsigned int len = end - start;
        if (wstr.length() != len)
        {
            return false;
        }
        return (d >= m_min && d <= m_max);
    }
}

int NumberInput::getInteger()
{
    string str = Utils::wstring2string(getText());
    return atoi(str.c_str());
}

double NumberInput::getDouble()
{
    string str = Utils::wstring2string(getText());
    return atof(str.c_str());
}

