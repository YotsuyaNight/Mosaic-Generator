#include "mosaic.h"

namespace MosaicGenerator {

Mosaic::Mosaic(int rows, int cols, int tw, int th)
    : m_rows(rows), m_cols(cols), m_tw(tw), m_th(th)
{
    m_tiles = QVector<QVector<PixelMap*>>();
    for (int x = 0; x < rows; x++) {
        QVector<PixelMap*> row;
        for (int y = 0; y < cols; y++) {
            PixelMap *pm = new PixelMap(tw, th);
            row.append(pm);
        }
        m_tiles.append(row);
    }
}

Mosaic::~Mosaic()
{
    for (QVector<PixelMap*> row : m_tiles) {
        qDeleteAll(row);
    }
}

//Getters

PixelMap& Mosaic::getTile(int x, int y)
{
    return *m_tiles[x][y];
}

int Mosaic::rows()
{
    return m_rows;
}

int Mosaic::columns()
{
    return m_cols;
}

int Mosaic::tileHeight()
{
    return m_th;
}

int Mosaic::tileWidth()
{
    return m_tw;
}

}