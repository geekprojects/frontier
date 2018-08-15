
#include <beyond/fonts.h>

using namespace std;

FontFace::FontFace(
    FontManager* manager,
    string path,
    int style,
    int height,
    int unitsPerEM)
{
    m_manager = manager;
    m_path = path;
    m_style = style;
    m_height = height;
    m_unitsPerEM = unitsPerEM;

    m_references = 0;
    m_face = NULL;
}

FontFace::~FontFace()
{
}

FontHandle* FontFace::open(int pointSize)
{
    FT_Error error;

    if (m_face == NULL)
    {
        error = FT_New_Face(
            m_manager->getFTLibrary(),
            m_path.c_str(),
            0,
            &m_face);
        if (error != 0)
        {
            return NULL;
        }
    }

    m_references++;

    FontHandle* handle = new FontHandle(this, pointSize);
    return handle;
}

void FontFace::close(FontHandle* handle)
{
    m_references--;
    if (m_references <= 0)
    {
        // Free font
    }
    delete handle;
}

FT_Face FontFace::getFTFace()
{
    return m_face;
}

