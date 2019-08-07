#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMutex>
#include <QThread>
#include "iconrepository.h"
#include "mosaic.h"

namespace MosaicGenerator {

class GeneratorRunner;

class Generator : public QObject
{
    Q_OBJECT
    friend class GeneratorRunner;

public:
    explicit Generator(QImage source, IconRepository* ir, int tw, int th);

    void generate();
    IconRepository* iconRepository();
    Mosaic* mosaic();
    void setThreadCount(int n);

signals:
    void finished();

private slots:
    void slotRunnerFinished(GeneratorRunner *thread);

private:
    void nextTile();

    int m_threadCount = 1;
    Mosaic *m_source;
    Mosaic *m_mosaic;
    IconRepository *m_repository;
    QVector<GeneratorRunner*> m_runners;
    QMutex m_repoAccessMutex;
    int m_nextRow;
    int m_nextCol;
    bool m_lastTile;
};

class GeneratorRunner : public QThread
{
    Q_OBJECT

public:
    GeneratorRunner(Generator* parent, int threadNumber, int threadCount);
    void run() override;

    Generator *m_parent;
    int m_threadNumber;
    int m_threadCount;
    
signals:
    void finished(GeneratorRunner *thread);

};

}

#endif