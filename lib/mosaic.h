#ifndef MOSAIC_H
#define MOSAIC_H

#include "pixelmap.h"
#include <QImage>
#include <QVector>

namespace MosaicGenerator {

class Mosaic
{
public:
    explicit Mosaic(int rows, int cols, int tw, int th);
    virtual ~Mosaic();

    PixelMap& getTile(int x, int y);
    int rows();
    int columns();
    int tileWidth();
    int tileHeight();

private:
    int m_rows;
    int m_cols;
    int m_tw;
    int m_th;
    QVector<QVector<PixelMap*>> m_tiles;
};

}

#endif