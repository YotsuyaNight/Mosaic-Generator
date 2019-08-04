#include "generator.h"

namespace MosaicGenerator {

Generator::Generator(QImage source, IconRepository* ir, int tw, int th)
    : m_repository(ir)
{
    source.convertTo(QImage::Format_ARGB32);
    m_source = new Mosaic(source, tw, th);
    m_mosaic = new Mosaic(m_source->rows(), m_source->columns(), tw, th);
}

void Generator::generate()
{
    int i = 0;
    QVector<PixelMap*> icons = m_repository->icons();
    for (int x = 0; x < m_mosaic->rows(); x++) {
        for (int y = 0; y < m_mosaic->columns(); y++) {
            m_mosaic->setTile(x, y, icons[i]);
            i = (i + 1) % icons.size();
        }
    }
}

IconRepository* Generator::iconRepository()
{
    return m_repository;
}

Mosaic* Generator::mosaic()
{
    return m_mosaic;
}

}
