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

#ifndef __FRONTIER_STYLES_CSS_PARSER_H_
#define __FRONTIER_STYLES_CSS_PARSER_H_

#include <string>
#include <vector>
#include <map>

#include <geek/core-logger.h>
#include <frontier/styles.h>

namespace Frontier {

class CssParser : public Geek::Logger
{
 private:
    StyleEngine* m_styleEngine;

 public:
    CssParser(StyleEngine* styleEngine);
    virtual ~CssParser();

    bool parse(std::string path);
};

};

#endif

