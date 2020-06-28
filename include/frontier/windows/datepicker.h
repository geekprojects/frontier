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

#ifndef __FRONTIER_WINDOWS_DATE_PICKER_H_
#define __FRONTIER_WINDOWS_DATE_PICKER_H_

#include <frontier/window.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/combobox.h>
#include <frontier/widgets/grid.h>

namespace Frontier
{


/**
 * \brief Date Picker Window
 *
 * Allows a user to select a date
 *
 * \ingroup windows
 */
class DatePickerWindow : public Frontier::FrontierWindow
{
 private:
    int m_currentMonth;
    int m_currentYear;
    int m_selectedDay;
    int m_selectedMonth;
    int m_selectedYear;

    ComboBox* m_monthInput;
    TextInput* m_yearInput;

    Grid* m_dayGrid;

    sigc::signal<bool, int, int, int> m_dateSelectSignal;

    void onDateSelected(Widget* button);
    void onMonthSelected(ListItem* item);
    void onPrevMonth(Widget* button);
    void onNextMonth(Widget* button);

 public:
    DatePickerWindow(Frontier::FrontierApp* app);
    DatePickerWindow(Frontier::FrontierApp* app, int year, int month, int day);
    virtual ~DatePickerWindow();

    bool init();
    bool update();

    sigc::signal<bool, int, int, int> dateSelectSignal() { return m_dateSelectSignal; }
};

};

#endif
