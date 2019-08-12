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

#include "iconrepository.h"
#include "pixelmap.h"
#include <QDir>
#include <QDebug>

namespace MosaicGenerator {

IconRepository::IconRepository(QString path, int size)
    : m_iconSize(size)
{
    //Scan directory for image files
    QDir directory(path);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    directory.setNameFilters(filters);
    //Turn images into PixelMap objects
    for (QFileInfo file : directory.entryInfoList()) {
        QImage image = QImage(file.absoluteFilePath()).scaled(size, size);
        image.convertTo(QImage::Format_ARGB32);
        PixelMap *pm = new PixelMap(image);
        m_icons.append(pm);
    }
}

IconRepository::~IconRepository()
{
    qDeleteAll(m_icons);
}

QVector<PixelMap*> IconRepository::icons()
{
    return m_icons;
}

int IconRepository::iconSize()
{
    return m_iconSize;
}

}
