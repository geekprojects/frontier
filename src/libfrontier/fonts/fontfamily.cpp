
#include <beyond/fonts.h>

using namespace std;

FontFamily::FontFamily()
{
}

FontFamily::~FontFamily()
{
    vector<FontFace*>::iterator it;
    for (it = m_faces.begin(); it != m_faces.end(); it++)
    {
        FontFace* face = *it;
        delete face;
    }
}

void FontFamily::addFace(FontFace* face)
{
    m_faces.push_back(face);
}

FontFace* FontFamily::getFace(int style)
{
    vector<FontFace*>::iterator it;
    for (it = m_faces.begin(); it != m_faces.end(); it++)
    {
        FontFace* face = *it;
        if (face->getStyle() == style)
        {
            return face;
        }
    }
    return NULL;
}

