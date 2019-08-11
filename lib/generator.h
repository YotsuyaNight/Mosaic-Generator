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

#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMutex>
#include "iconrepository.h"
#include "mosaic.h"

class QThread;

namespace MosaicGenerator {

class GeneratorRunner;

class Generator : public QObject
{
    Q_OBJECT
    friend class GeneratorRunner;

public:
    explicit Generator(QImage source, IconRepository* ir, int tw, int th);
    ~Generator();

    void generate();
    IconRepository* iconRepository();
    Mosaic* mosaic();
    int maxProgress();
    void setThreadCount(int n);
    void setRandomness(int n);

signals:
    void finished();
    void progressTick(int progress);

private slots:
    void slotRunnerFinished();

private:
    void nextTile();

    int m_threadCount = 1;
    int m_remainingRunners;
    int m_randomness = 1;
    Mosaic *m_source;
    Mosaic *m_mosaic;
    IconRepository *m_repository;
    QVector<QThread*> m_runners;
    QMutex m_repoAccessMutex;
    int m_nextRow;
    int m_nextCol;
    bool m_lastTile;
};

class GeneratorRunner : public QObject
{
    Q_OBJECT

public:
    explicit GeneratorRunner(Generator* parent);
    Generator *m_parent;

public slots:
    void process();

signals:
    void finished();

};

}

#endif
