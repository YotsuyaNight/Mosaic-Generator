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
    int rows = m_parent->m_mosaic->rows();
    int cols = m_parent->m_mosaic->columns();
    //Each tile
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            
            if ((x*cols+y) % m_threadCount != m_threadNumber) {
                continue;
            }

            qDebug() << "Thread #" << m_threadNumber << ": Generating tile " 
                     << x * cols + y << "of" 
                     << rows * cols;

            PixelMap sourceTile = m_parent->m_source->getTile(x, y);
            PixelMap *bmu = nullptr;
            int bmuDistance = 0;
            for (PixelMap *unit : icons) {
                if (cooldown.contains(unit)) {
                    continue;
                }
                int distance = sourceTile.distance(unit);
                if (bmu == nullptr || distance < bmuDistance) {
                    bmu = unit;
                    bmuDistance = distance;
                }
            }
            m_parent->m_mosaic->setTile(x, y, bmu);
            
            cooldown.insert(bmu, 100);
            for (PixelMap *key : cooldown.keys()) {
                if (cooldown.value(key) == 1) {
                    cooldown.remove(key);
                } else {
                    cooldown[key]--;
                }
            }

        }
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
    //Spawning threads
    for (int i = 0; i < m_threadCount; i++) {
        GeneratorRunner *t = new GeneratorRunner(this, i, m_threadCount);
        m_runners.append(t);
        connect(t, &GeneratorRunner::finished, this, &Generator::slotRunnerFinished);
        t->start();
    }
}

void Generator::slotRunnerFinished(GeneratorRunner *thread) {
    m_runners.removeOne(thread);
    thread->wait();
    delete thread;
    if (m_runners.size() == 0) {
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
