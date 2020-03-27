
#include <frontier/engines/embedded.h>

using namespace Frontier;

EmbeddedWindow::EmbeddedWindow(Frontier::FrontierEngine* engine, Frontier::FrontierWindow* window)
    : FrontierEngineWindow(engine, window)
{
    m_position.x = 0;
    m_position.y = 0;
}

EmbeddedWindow::~EmbeddedWindow()
{
}

bool EmbeddedWindow::init()
{
    return true;
}

void EmbeddedWindow::show()
{
}

void EmbeddedWindow::hide()
{
}

bool EmbeddedWindow::update()
{
    return true;
}

float EmbeddedWindow::getScaleFactor()
{
    return ((EmbeddedEngine*)m_engine)->getScaleFactor();
}

