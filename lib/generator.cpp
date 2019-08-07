#include <QDebug>
#include <QMap>
#include "generator.h"

namespace MosaicGenerator {

GeneratorRunner::GeneratorRunner(Generator *parent, int threadNumber, int threadCount)
    : m_parent(parent), m_threadNumber(threadNumber), m_threadCount(threadCount)
{
}

void GeneratorRunner::run()
{
    QVector<PixelMap*> icons = m_parent->m_repository->icons();
    QMap<PixelMap*, int> cooldown;
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
        PixelMap *bmu = nullptr;
        int bmuDistance = 0;
        for (PixelMap *unit : icons) {
            int distance = sourceTile.distance(unit);
            if (bmu == nullptr || distance < bmuDistance) {
                bmu = unit;
                bmuDistance = distance;
            }
        }
        m_parent->m_mosaic->setTile(x, y, bmu);
        
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
        GeneratorRunner *t = new GeneratorRunner(this, i, m_threadCount);
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

void Generator::setThreadCount(int n)
{
    m_threadCount = n;
}

}
