
#include <frontier/frontier.h>
#include <frontier/engine.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Geek::Gfx;

FrontierWindow::FrontierWindow(FrontierApp* app)
{
    m_app = app;
    m_engineWindow = NULL;
}

FrontierWindow::~FrontierWindow()
{
}

bool FrontierWindow::init()
{
    if (m_engineWindow == NULL)
    {
        return m_app->getEngine()->initWindow(this);
    }
    return true;
}

void FrontierWindow::setContent(Widget* content)
{
    m_widget = content;
    m_widget->setPosition(0, 0);
}

void FrontierWindow::show()
{
    init();

    m_engineWindow->show();

    update();
}

void FrontierWindow::update()
{
    init();

    m_widget->calculateSize();

    m_surface = new Surface(getWidth(), getHeight(), 4);
    m_surface->clear(0x0);
    m_widget->draw(m_surface);

    m_engineWindow->update();
}

int FrontierWindow::getWidth()
{
    if (m_widget != NULL)
    {
        return m_widget->getWidth();
    }
    return 0;
}

int FrontierWindow::getHeight()
{
    if (m_widget != NULL)
    {
        return m_widget->getHeight();
    }
    return 0;
}

void FrontierWindow::postMessage(Message* message)
{
}

bool FrontierWindow::handleMessage(Message* message)
{
    Widget* t = m_widget->handleMessage(message);

if (t != NULL && t->isDirty())
{
update();
}

    m_lastEventTarget = t;
}

