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

#include <QDebug>
#include <QMap>
#include <cstdlib>
#include "generator.h"

namespace MosaicGenerator {

GeneratorRunner::GeneratorRunner(Generator *parent)
    : m_parent(parent)
{
}

void GeneratorRunner::run()
{
    QVector<PixelMap*> icons = m_parent->m_repository->icons();
    while (true) {

        //Obtain mutex and get next tile
        m_parent->m_repoAccessMutex.lock();
        if (m_parent->m_lastTile) {
            m_parent->m_repoAccessMutex.unlock();
            break;
        }
        int x = m_parent->m_nextRow;
        int y = m_parent->m_nextCol;
        PixelMap sourceTile = m_parent->m_source->getTile(x, y);
        m_parent->nextTile();
        m_parent->m_repoAccessMutex.unlock();

        //Process
        QMap<int, PixelMap*> sortedUnits;
        for (PixelMap *unit : icons) {
            int distance = sourceTile.distance(unit);
            sortedUnits.insert(distance, unit);
        }
        //Choose random tile
        int random = 1 + (std::rand() % m_parent->m_randomness);
        QMapIterator<int, PixelMap*> unitsIterator(sortedUnits);
        for (int i = 0; i < random; i++) {
            unitsIterator.next();
        }
        m_parent->m_mosaic->setTile(x, y, unitsIterator.value());
        
    }
    emit finished(this);
}

Generator::Generator(QImage source, IconRepository* ir, int tw, int th)
    : m_repository(ir)
{
    source.convertTo(QImage::Format_ARGB32);
    m_source = new Mosaic(source, tw, th);
    m_mosaic = new Mosaic(m_source->rows(), m_source->columns(), tw, th);
}

void Generator::generate()
{
    m_nextRow = 0;
    m_nextCol = 0;
    m_lastTile = false;
    //Spawning threads
    for (int i = 0; i < m_threadCount; i++) {
        GeneratorRunner *t = new GeneratorRunner(this);
        m_runners.append(t);
        connect(t, &GeneratorRunner::finished, this, &Generator::slotRunnerFinished);
        t->start();
    }
}

void Generator::nextTile()
{
    m_nextCol++;
    if (m_nextCol == m_source->columns()) {
        m_nextCol = 0;
        m_nextRow++;
    }
    if (m_nextRow == m_source->rows()) {
        m_lastTile = true;
    }
    emit progressTick(m_nextRow * m_source->columns() + m_nextCol);
}

void Generator::slotRunnerFinished(GeneratorRunner *thread) {
    m_runners.removeOne(thread);
    thread->wait();
    delete thread;
    if (m_runners.isEmpty()) {
        emit finished();
    }
}

IconRepository* Generator::iconRepository()
{
    return m_repository;
}

Mosaic* Generator::mosaic()
{
    return m_mosaic;
}

int Generator::maxProgress()
{
    return m_source->rows() * m_source->columns();
}

void Generator::setThreadCount(int n)
{
    m_threadCount = n;
}

void Generator::setRandomness(int n)
{
    m_randomness = n;
}

}
