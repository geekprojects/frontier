#ifndef __FRONTIER_WIDGETS_NUMBER_INPUT_H_
#define __FRONTIER_WIDGETS_NUMBER_INPUT_H_

#include <frontier/widgets/textinput.h>

namespace Frontier
{

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
