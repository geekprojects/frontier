
#include <frontier/frontier.h>

using namespace std;
using namespace Geek;
using namespace Geek::Gfx;

UITheme::UITheme(FrontierApp* app)
{
    m_app = app;
    m_initialised = false;

    m_font = NULL;
    m_iconFont = NULL;
}

bool UITheme::init()
{
    if (!m_initialised)
    {
        m_font = m_app->getFontManager()->openFont(
            "Lato",
            FontStyle_Normal,
            26);
            m_initialised = true;

        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: Lato\n");
            return false;
        }

        m_iconFont = m_app->getFontManager()->openFont(
            "FontAwesome",
            FontStyle_Normal,
            26);
            m_initialised = true;
        if (m_font == NULL)
        {
printf("UITheme::init: Failed to find font: FontAwesome\n");
            return false;
        }

        m_initialised = true;
    }
    return true;
}

UITheme::~UITheme()
{
}

void UITheme::drawBorder(Surface* surface, UIBorderType type, UIState state, int x, int y, int width, int height)
{
    uint32_t g1 = 0xff888888;
    uint32_t g2 = 0xff555555;
    uint32_t b1 = 0xffffffff;
    uint32_t b2 = 0xff000000;

    if (state == STATE_SELECTED)
    {
        uint32_t tmp;
        tmp = g1;
        g1 = g2;
        g2 = tmp;
        tmp = b1;
        b1 = b2;
        b2 = tmp;
    }

    surface->drawGrad(x, y, width, height, g1, g2);

    surface->drawLine(x, y, x + width, y, b1);
    surface->drawLine(x, y, x, y + height, b1);

    surface->drawLine(x + width, y, x + width, y + height, b2);
    surface->drawLine(x, y + height, x + width, y + height, b2);
}

void UITheme::drawText(Geek::Gfx::Surface* surface, int x, int y, std::wstring text, bool inverted)
{
    uint32_t c = 0xffffffff;
    if (inverted)
    {
        c = 0xff000000;
    }

    FontManager* fm = m_app->getFontManager();
    fm->write(m_font,
        surface,
        x,
        y,
        text.c_str(),
        c,
        true,
        NULL);
}

int UITheme::getTextWidth(std::wstring text)
{
    FontManager* fm = m_app->getFontManager();
    return fm->width(m_font, text.c_str());
}

int UITheme::getTextHeight()
{
    FontManager* fm = m_app->getFontManager();
    return m_font->getPixelHeight(72);
}

void UITheme::drawIcon(Geek::Gfx::Surface* surface, int x, int y, wchar_t icon, bool inverted)
{
    uint32_t c = 0xffffffff;
    if (inverted)
    {
        c = 0xff000000;
    }

    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    fm->write(m_iconFont,
        surface,
        x,
        y,
        text,
        c,
        true,
        NULL);
}

int UITheme::getIconWidth(wchar_t icon)
{
    wstring text = L"";
    text += icon;

    FontManager* fm = m_app->getFontManager();
    return fm->width(m_iconFont, text);
}

int UITheme::getIconHeight()
{
    return m_iconFont->getPixelHeight(72);
}


