#include <algorithm>
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
            m_data[x][y] = image.pixel(y, x);
        }
    }
}

PixelMap::~PixelMap()
{
    for (int x = 0; x < m_h; x++) {
        delete[] m_data[x];
    }
    delete[] m_data;
}

void PixelMap::copyFrom(PixelMap *pm)
{
    int h = std::min(m_h, pm->m_h);
    int w = std::min(m_w, pm->m_w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            m_data[x][y] = pm->m_data[x][y];
        }
    }
}

uint* PixelMap::operator[](std::size_t idx)
{
    return m_data[idx];
}

inline int red(uint color) {
    return ((color >> 24) & 0xFF);
}

inline int green(uint color) {
    return ((color >> 16) & 0xFF);
}

inline int blue(uint color) {
    return ((color >> 8) & 0xFF);
}

int PixelMap::distance(PixelMap *pm)
{
    int distance = 0;
    int h = std::min(m_h, pm->m_h);
    int w = std::min(m_w, pm->m_w);
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            distance += std::abs(red(m_data[x][y]) - red(pm->m_data[x][y]))
                     +  std::abs(green(m_data[x][y]) - green(pm->m_data[x][y]))
                     +  std::abs(blue(m_data[x][y]) - blue(pm->m_data[x][y]));
        }
    }
    return distance;
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
