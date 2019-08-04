#include <QMap>
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

    //Each tile
    for (int x = 0; x < m_mosaic->rows(); x++) {
        for (int y = 0; y < m_mosaic->columns(); y++) {

            PixelMap sourceTile = m_source->getTile(x, y);
            QMap<int, PixelMap*> bmuMap;
            for (PixelMap *unit : icons) {
                int distance = sourceTile.distance(unit);
                bmuMap.insert(distance, unit);
            }
            PixelMap *bmu = bmuMap.begin().value();
            m_mosaic->setTile(x, y, bmu);

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
