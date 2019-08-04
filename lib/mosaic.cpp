#include "mosaic.h"

namespace MosaicGenerator {

void Mosaic::initialize(int rows, int cols, int tw, int th)
{
    m_rows = rows;
    m_cols = cols;
    m_tw = tw;
    m_th = th;
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

Mosaic::Mosaic(int rows, int cols, int tw, int th)
{
    initialize(rows, cols, tw, th);
}

Mosaic::Mosaic(QImage image, int tw, int th)
{
    int rows = image.height() / th;
    int cols = image.width() / tw;
    initialize(rows, cols, tw, th);
    for (int x = 0; x < m_rows; x++) {
        for (int y = 0; y < m_cols; y++) {
            for (int i = 0; i < m_th; i++) {
                for (int j = 0; j < m_tw; j++) {
                    getTile(x,y)[i][j] = image.pixel(x * th + i, y * tw + j);
                }
            }
        }
    }
}

Mosaic::~Mosaic()
{
    for (QVector<PixelMap*> row : m_tiles) {
        qDeleteAll(row);
    }
}

QImage Mosaic::toImage()
{
    QImage img(m_cols * m_tw, m_rows * m_th, QImage::Format::Format_ARGB32);
    img.fill(0);
    for (int x = 0; x < m_rows; x++) {
        for (int y = 0; y < m_cols; y++) {
            for (int i = 0; i < m_th; i++) {
                for (int j = 0; j < m_tw; j++) {
                   img.setPixel(x * m_th + i, y * m_tw + j, getTile(x,y)[i][j]);
                }
            }
        }
    }
    return img;
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