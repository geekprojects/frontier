
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace Frontier;

class DemoApp : public FrontierApp
{
 private:
    FrontierWindow* m_mainWindow;

    void onTextButton();
    void onIconButton();

 public:
    DemoApp();
    ~DemoApp();

    virtual bool init();
};

using namespace Frontier;

DemoApp::DemoApp()
{
}

DemoApp::~DemoApp()
{
}

bool DemoApp::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

        Frame* frame1 = new Frame(this, false);

        Frame* toolbar = new Frame(this, true);
        toolbar->add(new IconButton(this, FRONTIER_ICON_FOLDER_OPEN));
        toolbar->add(new IconButton(this, FRONTIER_ICON_SAVE));
        toolbar->add(new IconButton(this, FRONTIER_ICON_SYNC));
        frame1->add(toolbar);

    Frame* labelFrame = new Frame(this, true);
    labelFrame->add(new Label(this, L"Label:"));
    labelFrame->add(new Label(this, L"I'm a label!"));
    frame1->add(labelFrame);

    Frame* buttonFrame = new Frame(this, true);
    Button* textButton;
    buttonFrame->add(new Label(this, L"Button:"));
    buttonFrame->add(textButton = new Button(this, L"Click me!"));
    frame1->add(buttonFrame);

    Frame* iconButtonFrame = new Frame(this, true);
    IconButton* iconButton;
    iconButtonFrame->add(new Label(this, L"Icon Button:"));
    iconButtonFrame->add(iconButton = new IconButton(this, 0xf0ae));
    frame1->add(iconButtonFrame);

    textButton->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onTextButton));
    iconButton->clickSignal().connect(sigc::mem_fun(*this, &DemoApp::onIconButton));

#if 1
    Frame* listFrame = new Frame(this, true);
    listFrame->add(new Label(this, L"List:"));

    List* list = new List(this);
    list->addItem(new TextListItem(L"This is"));
    list->addItem(new TextListItem(L"a list"));
    list->addItem(new TextListItem(L"with lots"));
    list->addItem(new TextListItem(L"of very"));
    list->addItem(new TextListItem(L"boring"));
    list->addItem(new TextListItem(L"items"));
    Scroller* scroller = new Scroller(this);
    scroller->setChild(list);
    listFrame->add(scroller);
    frame1->add(listFrame);
#endif

    m_mainWindow = new FrontierWindow(this);
    m_mainWindow->setContent(frame1);

    m_mainWindow->show();

    return true;
}

void DemoApp::onIconButton()
{
    printf("DemoApp::onIconButton: Here!\n");
}

void DemoApp::onTextButton()
{
    printf("DemoApp::onTextButton: Here!\n");
}

int main(int argc, char** argv)
{
    DemoApp app;

    app.init();

    app.main();

    return 0;
}


