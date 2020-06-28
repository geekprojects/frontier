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

#ifndef __FRONTIER_WIDGETS_NUMBER_INPUT_H_
#define __FRONTIER_WIDGETS_NUMBER_INPUT_H_

#include <frontier/widgets/textinput.h>

namespace Frontier
{

/**
 * \brief A TextInput widget that only allows numbers
 *
 * \ingroup widgets
 */
class NumberInput : public TextInput
{
 private:
    double m_min;
    double m_max;
    bool m_integerOnly;

    void init();

 public:
    NumberInput(FrontierApp* ui);
    NumberInput(FrontierWindow* ui);
    virtual ~NumberInput();

    virtual void calculateSize();

    void setMin(double min);
    double getMin() { return m_min; }
    void setMax(double max);
    double getMax() { return m_max; }
    void setIntegerOnly(bool integerOnly) { m_integerOnly = integerOnly; }
    bool getIntegerOnly() { return m_integerOnly; }

    void setNumber(int i);
    void setNumber(double d);
    int getInteger();
    double getDouble();

    virtual bool isValid(std::wstring str);
};

};

#endif
