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


#include <frontier/utils.h>

#include <execinfo.h>


using namespace Frontier;
using namespace std;

#define BT_BUF_SIZE 100

wstring Utils::string2wstring(string str)
{
    wstring out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += (char)str[i];
    }
    return out;
}

string Utils::wstring2string(wstring str)
{
    string out;
    unsigned int i;
    for (i = 0; i < str.length(); i++)
    {
        out += str[i];
    }
    return out;
}

bool Utils::compare(std::string str1, std::wstring str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }

    int i;
    for (i = 0; i < str1.length(); i++)
    {
        if (str1.at(i) != str2.at(i))
        {
            return false;
        }
    }
    return true;
}

void Utils::stacktrace()
{
    char **strings;
    void *buffer[BT_BUF_SIZE];
    int j;
    int nptrs;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings != NULL)
    {
        for (j = 0; j < nptrs; j++)
        {
            printf("%s\n", strings[j]);
        }
        free(strings);
    }
}



