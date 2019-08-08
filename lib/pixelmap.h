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

#ifndef PIXELMAP_H
#define PIXELMAP_H

#include <QImage>
#include <QHash>

typedef unsigned int uint;

namespace MosaicGenerator {

class PixelMap
{
public:
    explicit PixelMap(int w, int h);
    explicit PixelMap(const QImage &image);
    virtual ~PixelMap();

    void copyFrom(PixelMap *pm);
    uint* operator[](std::size_t idx);
    int distance(PixelMap *pm);

    QString toString();

private:
    uint **m_data;
    uint m_w;
    uint m_h;
};

}

#endif
