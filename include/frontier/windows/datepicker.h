#ifndef __FRONTIER_WINDOWS_DATE_PICKER_H_
#define __FRONTIER_WINDOWS_DATE_PICKER_H_

#include <frontier/window.h>
#include <frontier/widgets/textinput.h>
#include <frontier/widgets/combobox.h>
#include <frontier/widgets/grid.h>

namespace Frontier
{

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
