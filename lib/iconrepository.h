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

#ifndef ICONREPOSITORY_H
#define ICONREPOSITORY_H

#include <QString>
#include <QImage>

namespace MosaicGenerator {

class PixelMap;

class IconRepository
{
public:
    explicit IconRepository(QString path, int size);
    virtual ~IconRepository();

    QVector<PixelMap*> icons();
    int iconSize();

private:
    QVector<PixelMap*> m_icons;
    int m_iconSize;
};

}

#endif
