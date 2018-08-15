
#include <beyond/fonts.h>

using namespace std;

FontHandle::FontHandle(FontFace* face, int pointSize)
{
    m_face = face;
    m_pointSize = pointSize;
}

FontHandle::~FontHandle()
{
}

FT_Face FontHandle::getFTFace()
{
    return m_face->getFTFace();
}

int FontHandle::getPixelHeight(int dpi)
{
    map<int, int>::iterator it;
    it = m_pixelSizes.find(dpi);
    if (it != m_pixelSizes.end())
    {
        return it->second;
    }

    FT_Face ftFace = m_face->getFTFace();
    float heightf = (ftFace->height * ((float)m_pointSize * (float)dpi / 72.0f)) / ftFace->units_per_EM;
    int height = (int)heightf;

    m_pixelSizes.insert(make_pair(dpi, height));
    return height;
}

