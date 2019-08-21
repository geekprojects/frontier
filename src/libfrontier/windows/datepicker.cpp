
#include <frontier/windows/datepicker.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/iconbutton.h>
#include <frontier/widgets/label.h>
#include <frontier/fontawesome.h>

#include <chrono>

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

DatePickerWindow::~DatePickerWindow()
{
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
    dateFrame->add(prevButton = new IconButton(this, getApp()->getTheme()->getIcon(FRONTIER_ICON_ANGLE_LEFT)));
    dateFrame->add(m_monthInput = new ComboBox(this));
    dateFrame->add(m_yearInput = new TextInput(this, L"2019"));
    dateFrame->add(nextButton = new IconButton(this, getApp()->getTheme()->getIcon(FRONTIER_ICON_ANGLE_RIGHT)));
    root->add(dateFrame);

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

    wchar_t buf[5];

    swprintf(buf, 5, L"%d", m_currentYear);
    m_yearInput->setText(buf);

    m_dayGrid->clear();

    m_dayGrid->put(0, 0, new Label(this, L"Mon"));
    m_dayGrid->put(1, 0, new Label(this, L"Tue"));
    m_dayGrid->put(2, 0, new Label(this, L"Wed"));
    m_dayGrid->put(3, 0, new Label(this, L"Thu"));
    m_dayGrid->put(4, 0, new Label(this, L"Fri"));
    m_dayGrid->put(5, 0, new Label(this, L"Sat"));
    m_dayGrid->put(6, 0, new Label(this, L"Sun"));
    // second, minute, hour 1-based day, 0-based month, year since 1900
    std::tm time_in = { 0, 0, 0, 1, m_currentMonth - 1, m_currentYear - 1900 };

    std::time_t time_temp = std::mktime(&time_in);
    const std::tm * time_out = std::localtime(&time_temp);

    int firstwday = time_out->tm_wday;
    if (firstwday == 0)
    {
        firstwday = 6;
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

                Button* button = new Button(this, buf);
                button->setPrivateData((void*)(uint64_t)((day << 24) | (m_currentMonth << 16) | (m_currentYear)));
                button->clickSignal().connect(sigc::mem_fun(*this, &DatePickerWindow::onDateSelected));

                if (day == m_selectedDay && m_currentMonth == m_selectedMonth && m_currentYear == m_selectedYear)
                {
                    button->setHighlight(true);
                }
                m_dayGrid->put(x, y + 1, button);
            }
        }
    }

    log(DEBUG, "update: Done!");

    return true;
}

void DatePickerWindow::onDateSelected(Button* button)
{
    uint64_t data = (uint64_t)(button->getPrivateData());
    int day = (data >> 24) & 0xf;
    int month = (data >> 16) & 0xf;
    int year = (data & 0xffff);

    log(DEBUG, "onDateSelected: day=%d, month=%d, year=%d", day, month, year);

    m_dateSelectSignal.emit(day, month, year);
}

void DatePickerWindow::onPrevMonth(Button* button)
{
   m_currentMonth--;
   if (m_currentMonth < 1)
   {
       m_currentMonth = 12;
       m_currentYear--;
   }

   update();
}

void DatePickerWindow::onNextMonth(Button* button)
{
   m_currentMonth++;
   if (m_currentMonth > 12)
   {
       m_currentMonth = 1;
       m_currentYear++;
   }

   update();
}

