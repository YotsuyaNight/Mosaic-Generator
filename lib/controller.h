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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QImage;

namespace MosaicGenerator {

class Generator;
class IconRepository;

class Controller : public QObject
{
    Q_OBJECT

public:
    ~Controller();
    static Controller* self();

    void startGenerator();
    void setSourceImage(QString path);
    void setThreadCount(int n);
    void setRandomness(int n);
    void setIconSize(int px);
    void setImageBlockSize(int px);
    int loadIconRepository(QString path);
    QImage mosaic();
    int maxProgress();

signals:
    void generatorFinished();
    void generatorProgress(int progress);

private:
    Controller();

    inline static Controller *m_self = nullptr;
    IconRepository *m_repository = nullptr;
    Generator *m_generator = nullptr;
    QImage *m_sourceImage = nullptr;
    int m_threadCount;
    int m_randomness = 1;
    int m_iconSize = 1;
    int m_imageBlockSize = 1;
};

}

#endif
