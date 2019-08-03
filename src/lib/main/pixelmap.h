#ifndef PIXELMAP_H
#define PIXELMAP_H

#include <QImage>
#include <QHash>

namespace MosaicGenerator {

class PixelMap
{
typedef unsigned int uint;
public:
    explicit PixelMap(int w, int h);
    explicit PixelMap(const QImage &image);
    virtual ~PixelMap();

    uint* operator[](std::size_t idx);

    QString toString();

private:
    uint **m_data;
    uint m_w;
    uint m_h;
};

}

#endif
