
#include <frontier/frontier.h>
#include <frontier/widgets.h>

class DemoApp : public FrontierApp
{
 private:
    FrontierWindow* m_mainWindow;

 public:
    DemoApp();
    ~DemoApp();

    virtual bool init();

    virtual void handleMessage(Message* message);
};

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

    Frame* labelFrame = new Frame(this, true);
    labelFrame->add(new Label(this, L"Label:"));
    labelFrame->add(new Label(this, L"I'm a label!"));
    frame1->add(labelFrame);

    Frame* buttonFrame = new Frame(this, true);
    buttonFrame->add(new Label(this, L"Button:"));
    buttonFrame->add(new Button(this, L"Click me!"));
    frame1->add(buttonFrame);

    Frame* iconButtonFrame = new Frame(this, true);
    iconButtonFrame->add(new Label(this, L"Icon Button:"));
    iconButtonFrame->add(new IconButton(this, 0xf0ae));
    frame1->add(iconButtonFrame);

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

    m_mainWindow = new FrontierWindow(this);
    m_mainWindow->setContent(frame1);

    m_mainWindow->show();

    return true;
}

void DemoApp::handleMessage(Message* message)
{
    printf("DemoApp::handleMessage: Here!\n");
}

int main(int argc, char** argv)
{
    DemoApp app;

    app.init();

    app.main();

    return 0;
}


