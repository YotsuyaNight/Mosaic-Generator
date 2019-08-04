#ifndef GENERATOR_H
#define GENERATOR_H

#include "iconrepository.h"
#include "mosaic.h"

namespace MosaicGenerator {

class Generator
{
public:
    explicit Generator(QImage source, IconRepository* ir, int tw, int th);

    void generate();
    IconRepository* iconRepository();
    Mosaic* mosaic();

private:
    Mosaic *m_source;
    Mosaic *m_mosaic;
    IconRepository *m_repository;
};

}

#endif