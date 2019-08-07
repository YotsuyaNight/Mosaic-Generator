#include <QImage>
#include "controller.h"
#include "generator.h"

namespace MosaicGenerator {

Controller::Controller()
{
}

Controller::~Controller()
{
    delete m_repository;
    delete m_generator;
    delete m_sourceImage;
}

Controller* Controller::self()
{
    if (m_self == nullptr) {
        m_self = new Controller;
    }
    return m_self;
}

void Controller::startGenerator()
{
    if (m_generator != nullptr) {
        delete m_generator;
    }
    m_generator = new Generator(*m_sourceImage, m_repository, m_tw, m_th);
    m_generator->setThreadCount(m_threadCount);
    connect(m_generator, &Generator::progressTick, this, &Controller::generatorProgress);
    connect(m_generator, &Generator::finished, this, &Controller::generatorFinished);
    m_generator->generate();
}

void Controller::setIconRepository(IconRepository *repository)
{
    if (m_repository != nullptr) {
        delete m_repository;
    }
    m_repository = repository;
}

void Controller::setSourceImage(QImage *image)
{
    if (m_repository != nullptr) {
        delete m_sourceImage;
    }
    m_sourceImage = image;
}

QImage Controller::mosaic()
{
    return QImage();
}

int Controller::maxProgress()
{
    return m_generator->maxProgress();
}

void Controller::setThreadCount(int n)
{
    m_threadCount = n;
}

void Controller::setTileWidth(int px)
{
    m_tw = px;
}

void Controller::setTileHeight(int px)
{
    m_th = px;
}

}