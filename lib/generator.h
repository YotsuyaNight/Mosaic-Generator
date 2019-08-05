#ifndef GENERATOR_H
#define GENERATOR_H

#include <QThread>
#include "iconrepository.h"
#include "mosaic.h"

namespace MosaicGenerator {

class GeneratorRunner;

class Generator
{
    friend class GeneratorRunner;

public:
    explicit Generator(QImage source, IconRepository* ir, int tw, int th);

    void generate();
    IconRepository* iconRepository();
    Mosaic* mosaic();
    void setThreadCount(int n);

private:
    int m_threadCount = 1;
    Mosaic *m_source;
    Mosaic *m_mosaic;
    IconRepository *m_repository;
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
};

}

#endif