#include "pixelmap.h"

namespace MosaicGenerator {

PixelMap::PixelMap(int w, int h)
    : m_w(w), m_h(h)
{
    m_data = new uint*[m_h];
    for (int x = 0; x < m_h; x++) {
        m_data[x] = new uint[m_w];
        for (int y = 0; y < m_w; y++) {
            m_data[x][y] = 0;
        }
    }
}

PixelMap::PixelMap(const QImage &image)
{
    m_w = image.width();
    m_h = image.height();
    m_data = new uint*[m_h];
    for (int x = 0; x < m_h; x++) {
        m_data[x] = new uint[m_w];
        for (int y = 0; y < m_w; y++) {
            m_data[x][y] = image.pixel(x, y);
        }
    }
}

PixelMap::~PixelMap()
{
    for (int x = 0; x < m_h; x++) {
        delete m_data[x];
    }
    delete m_data;
}

uint* PixelMap::operator[](std::size_t idx)
{
    return m_data[idx];
}

QString PixelMap::toString()
{
    QStringList sl;
    sl << "[";
    for (int x = 0; x < m_h; x++) {
        QStringList row; 
        for (int y = 0; y < m_w; y++) {
            row << QString::number(m_data[x][y]);
        }
        sl << row.join(", ");
    }
    sl << "]";
    return sl.join("\\n");
}

}
