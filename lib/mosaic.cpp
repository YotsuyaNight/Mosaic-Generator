/*
* This file is part of "Mosaic Generator".
* 
* Copyright 2019 Marcin Dłubakowski <m.dlubakowski@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mosaic.h"

namespace MosaicGenerator {

void Mosaic::initialize(int rows, int cols, int tw, int th)
{
    m_rows = rows;
    m_cols = cols;
    m_tw = tw;
    m_th = th;
    m_tiles = new PixelMap**[rows];
    for (int x = 0; x < rows; x++) {
        PixelMap **row = new PixelMap*[cols];
        for (int y = 0; y < cols; y++) {
            PixelMap *pm = new PixelMap(tw, th);
            row[y] = pm;
        }
        m_tiles[x] = row;
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
                    getTile(x,y)[i][j] = image.pixel(y * m_tw + j, x * m_th + i);
                }
            }
        }
    }
}

Mosaic::~Mosaic()
{
    for (int x = 0; x < m_rows; x++) {
        for (int y = 0; y < m_cols; y++) {
            delete m_tiles[x][y];
        }
        delete[] m_tiles[x];
    }
    delete[] m_tiles;
}

void Mosaic::setTile(int x, int y, PixelMap* pm)
{
    getTile(x, y).copyFrom(pm);
}

QImage Mosaic::toImage()
{
    QImage img(m_cols * m_tw, m_rows * m_th, QImage::Format_ARGB32);
    for (int x = 0; x < m_rows; x++) {
        for (int y = 0; y < m_cols; y++) {
            for (int i = 0; i < m_tw; i++) {
                for (int j = 0; j < m_th; j++) {
                   img.setPixel(y * m_tw + j, x * m_th + i, getTile(x,y)[i][j]);
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