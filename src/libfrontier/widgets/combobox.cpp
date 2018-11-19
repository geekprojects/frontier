
#include <frontier/widgets/combobox.h>
#include <frontier/widgets/label.h>

using namespace std;
using namespace Geek;
using namespace Frontier;

ComboBox::ComboBox(FrontierApp* ui) : Frame(ui, true)
{
    initComboBox();
}

ComboBox::ComboBox(FrontierWindow* ui) : Frame(ui, true)
{
    initComboBox();
}

ComboBox::ComboBox(FrontierApp* ui, vector<wstring> options) : Frame(ui, true)
{
    m_options = options;

    initComboBox();
}

ComboBox::ComboBox(FrontierWindow* ui, vector<wstring> options) : Frame(ui, true)
{
    m_options = options;

    initComboBox();
}

ComboBox::~ComboBox()
{
}

void ComboBox::initComboBox()
{
    setMargin(0);
    setPadding(0);

    m_textInput = new TextInput(m_ui, L"");
    m_button = new IconButton(m_ui, FRONTIER_ICON_ARROW_DOWN);

    m_button->clickSignal().connect(sigc::mem_fun(*this, &ComboBox::openDropDown));

    add(m_textInput);
    add(m_button);

    m_comboBoxDropDown = new ComboBoxDropDown(m_ui);

    m_comboBoxDropDown->getList()->selectSignal().connect(sigc::mem_fun(*this, &ComboBox::optionSelected));

    updateOptions();
}

void ComboBox::updateOptions()
{
    m_comboBoxDropDown->getList()->clearItems();

    for (wstring option : m_options)
    {
        m_comboBoxDropDown->getList()->addItem(new TextListItem(m_comboBoxDropDown, option));
    }
}

void ComboBox::openDropDown()
{
    Vector2D widgetPos = getAbsolutePosition();
    widgetPos.y += m_textInput->getHeight() / 2;

    Vector2D screenPos = getWindow()->getScreenPosition(widgetPos);

    m_comboBoxDropDown->show();
    m_comboBoxDropDown->setPosition(screenPos);
    m_comboBoxDropDown->setSize(Size(m_textInput->getWidth(), 20));
}

void ComboBox::optionSelected(ListItem* option)
{
    printf("ComboBox::optionSelected: Here!\n");
    if (option != NULL)
    {
        wstring text = ((TextListItem*)option)->getText();
        m_textInput->setText(text);
    }
    m_comboBoxDropDown->hide();
}

ComboBoxDropDown::ComboBoxDropDown(FrontierApp* app) : FrontierWindow(app, L"", WINDOW_TOOL_TIP)
{
    setSize(Size(20, 20));

    Frame* frame = new Frame(this, false);
    frame->setBorder(true);
    m_list = new List(this);
    frame->add(m_list);
    setContent(frame);
}

ComboBoxDropDown::~ComboBoxDropDown()
{
}

bool ComboBoxDropDown::init()
{
    return true;
}

void ComboBoxDropDown::lostFocus()
{
    printf("ComboBoxDropDown::lostFocus: Closing!\n");
    hide();
}



