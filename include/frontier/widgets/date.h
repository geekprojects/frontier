#ifndef __FRONTIER_WIDGETS_DATE_H_
#define __FRONTIER_WIDGETS_DATE_H_

#include <frontier/widgets/frame.h>
#include <frontier/widgets/label.h>
#include <frontier/widgets/numberinput.h>

#include <chrono>

namespace Frontier
{

/**
 * \brief Displays a date and (optionally) time
 *
 * Clicking this Widget will open a DatePicker window
 *
 * \ingroup widgets
 */
class Date : public Frame
{
 private:
    bool m_hasValue;
    bool m_hasTime;
    std::chrono::seconds m_value;

    Label* m_dateLabel;
    Frontier::NumberInput* m_hourInput;
    Frontier::NumberInput* m_minuteInput;

    sigc::signal<void, std::chrono::seconds> m_signalValueChanged;

    void onDateClick(Widget* widget);
    void onTimeChanged(Frontier::TextInput* w);
    bool onDateSelect(int year, int month, int day);

    void updateDateTime();

 public:
    Date(FrontierApp* ui, bool hasTime);
    Date(FrontierApp* ui, bool hasTime, std::chrono::seconds value);
    ~Date();

    void setup();

    void setHasValue(bool hasValue);
    bool getHasValue() { return m_hasValue; }
    void setValue(std::chrono::seconds value);
    std::chrono::seconds getValue() { return m_value; }

    sigc::signal<void, std::chrono::seconds> signalValueChanged() { return m_signalValueChanged; }
};

};

#endif
