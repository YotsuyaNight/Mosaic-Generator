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
    explicit Mosaic(QImage image, int tw, int th);
    virtual ~Mosaic();

    void setTile(int x, int y, PixelMap* pm);
    QImage toImage();

    PixelMap& getTile(int x, int y);
    int rows();
    int columns();
    int tileWidth();
    int tileHeight();

private:
    void initialize(int rows, int cols, int tw, int th);

    int m_rows;
    int m_cols;
    int m_tw;
    int m_th;
    QVector<QVector<PixelMap*>> m_tiles;
};

}

#endif