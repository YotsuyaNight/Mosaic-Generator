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
    PixelMap ***m_tiles;
};

}

#endif