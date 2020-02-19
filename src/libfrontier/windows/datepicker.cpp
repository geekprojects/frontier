
#include <frontier/windows/datepicker.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/label.h>
#include <frontier/fontawesome.h>

#include <chrono>
#include <time.h>

using namespace Geek;
using namespace Frontier;
using namespace std;

static int getDaysInMonth(int month, int year)
{
    if (month == 2)
    {
        // Leap year?
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))	
        {
            return 29;
        }
        else	
        {
            return 28;
        }
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month==12)	
    {
        return 31;
    }
    else 		
    {
        return 30;
    }
}

DatePickerWindow::DatePickerWindow(Frontier::FrontierApp* app)
    : FrontierWindow(app, L"Date Picker", WINDOW_NORMAL)
{
    m_selectedDay = 19;
    m_selectedMonth = 8;
    m_selectedYear = 2019;
    m_currentMonth = m_selectedMonth;
    m_currentYear = m_selectedYear;
}

DatePickerWindow::DatePickerWindow(Frontier::FrontierApp* app, int year, int month, int day)
    : FrontierWindow(app, L"Date Picker", WINDOW_NORMAL)
{
    m_selectedDay = day;
    m_selectedMonth = month;
    m_selectedYear = year;
    m_currentMonth = m_selectedMonth;
    m_currentYear = m_selectedYear;
}


DatePickerWindow::~DatePickerWindow()
{
    log(DEBUG, "~DatePickerWindow: Deleting!");
}

/*
 * +---------------------+
 * |  19th <Month> 2019  |
 * +---------------------+
 * | [30] [1] [2] [3] [4]|
 *
 *
 *
 *
 */

bool DatePickerWindow::init()
{
    Frame* root = new Frame(this, false);

    Frame* dateFrame = new Frame(this, true);
    IconButton* prevButton;
    IconButton* nextButton;
    dateFrame->add(prevButton = new IconButton(getApp(), getApp()->getTheme()->getIcon(FRONTIER_ICON_ANGLE_LEFT)));
    dateFrame->add(m_monthInput = new ComboBox(getApp()));
    dateFrame->add(m_yearInput = new TextInput(getApp(), L"2019"));
    dateFrame->add(nextButton = new IconButton(getApp(), getApp()->getTheme()->getIcon(FRONTIER_ICON_ANGLE_RIGHT)));
    root->add(dateFrame);

    m_monthInput->addOption(L"January", (void*)1);
    m_monthInput->addOption(L"February", (void*)2);
    m_monthInput->addOption(L"March", (void*)3);
    m_monthInput->addOption(L"April", (void*)4);
    m_monthInput->addOption(L"May", (void*)5);
    m_monthInput->addOption(L"June", (void*)6);
    m_monthInput->addOption(L"July", (void*)7);
    m_monthInput->addOption(L"August", (void*)8);
    m_monthInput->addOption(L"September", (void*)9);
    m_monthInput->addOption(L"October", (void*)10);
    m_monthInput->addOption(L"November", (void*)11);
    m_monthInput->addOption(L"December", (void*)12);
    m_monthInput->updateOptions();
    m_monthInput->selectSignal().connect(sigc::mem_fun(*this, &DatePickerWindow::onMonthSelected));

    prevButton->clickSignal().connect(sigc::mem_fun(*this, &DatePickerWindow::onPrevMonth));
    nextButton->clickSignal().connect(sigc::mem_fun(*this, &DatePickerWindow::onNextMonth));

    m_dayGrid = new Grid(this);

    root->add(m_dayGrid);

    setContent(root);

    update();

    return true;
}

bool DatePickerWindow::update()
{
    log(DEBUG, "update: %d/%d", m_currentMonth, m_currentYear);

    m_monthInput->selectOption((void*)(uintptr_t)m_currentMonth);

    wchar_t buf[5];
    swprintf(buf, 5, L"%d", m_currentYear);
    m_yearInput->setText(buf);

    m_dayGrid->clear();

    m_dayGrid->put(0, 0, new Label(getApp(), L"Mon"));
    m_dayGrid->put(1, 0, new Label(getApp(), L"Tue"));
    m_dayGrid->put(2, 0, new Label(getApp(), L"Wed"));
    m_dayGrid->put(3, 0, new Label(getApp(), L"Thu"));
    m_dayGrid->put(4, 0, new Label(getApp(), L"Fri"));
    m_dayGrid->put(5, 0, new Label(getApp(), L"Sat"));
    m_dayGrid->put(6, 0, new Label(getApp(), L"Sun"));
    // second, minute, hour 1-based day, 0-based month, year since 1900
    std::tm time_in = { 0, 0, 0, 1, m_currentMonth - 1, m_currentYear - 1900 };

    std::time_t time_temp = std::mktime(&time_in);
    std::tm time_out;
    localtime_r(&time_temp, &time_out);

    int firstwday = time_out.tm_wday;
    if (firstwday == 0)
    {
        firstwday = 7;
    }

    int daysInMonth = getDaysInMonth(m_currentMonth, m_currentYear);
    log(DEBUG, "update: First weekday of month: %d", firstwday);

    int day = (-firstwday) + 2;
    int y;
    for (y = 0; day < daysInMonth; y++)
    {
        int x;
        for (x = 0; x < 7; x++, day++)
        {
            if (day >= 1 && day <= daysInMonth)
            {
                swprintf(buf, 5, L"%d", day);

                Button* button = new Button(getApp(), buf);
                button->setPrivateData((void*)(uint64_t)((day << 24) | (m_currentMonth << 16) | (m_currentYear)));
                button->clickSignal().connect(sigc::mem_fun(*this, &DatePickerWindow::onDateSelected));

                if (day == m_selectedDay && m_currentMonth == m_selectedMonth && m_currentYear == m_selectedYear)
                {
                    button->setWidgetClass(L"highlight");
                }
                m_dayGrid->put(x, y + 1, button);
            }
        }
    }

    log(DEBUG, "update: Done!");

    return true;
}

void DatePickerWindow::onDateSelected(Widget* button)
{
    uint64_t data = (uint64_t)(button->getPrivateData());
    m_selectedDay = (data >> 24) & 0xff;
    m_selectedMonth = (data >> 16) & 0xff;
    m_selectedYear = (data & 0xffff);

    log(DEBUG, "onDateSelected: day=%d, month=%d, year=%d", m_selectedDay, m_selectedMonth, m_selectedYear);

    bool close = m_dateSelectSignal.emit(m_selectedYear, m_selectedMonth, m_selectedDay);

    if (close)
    {
        getApp()->removeWindow(this);
    }
    else
    {
        update();
    }
}

void DatePickerWindow::onMonthSelected(ListItem* item)
{
    m_currentMonth = (int)(intptr_t)item->getPrivateData();
    update();
}

void DatePickerWindow::onPrevMonth(Widget* button)
{
   m_currentMonth--;
   if (m_currentMonth < 1)
   {
       m_currentMonth = 12;
       m_currentYear--;
   }

   update();
}

void DatePickerWindow::onNextMonth(Widget* button)
{
   m_currentMonth++;
   if (m_currentMonth > 12)
   {
       m_currentMonth = 1;
       m_currentYear++;
   }

   update();
}

