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
    //Prepare image
    int width = (m_sourceImage->width() / m_imageBlockSize) * m_repository->iconSize();
    int height = (m_sourceImage->height() / m_imageBlockSize) * m_repository->iconSize();
    QImage scaledImage = m_sourceImage->scaled(width, height, Qt::KeepAspectRatio);
    //Prepare and run generator
    m_generator = new Generator(scaledImage, m_repository, m_repository->iconSize(), m_repository->iconSize());
    m_generator->setThreadCount(m_threadCount);
    m_generator->setRandomness(m_randomness);
    connect(m_generator, &Generator::progressTick, this, &Controller::generatorProgress);
    connect(m_generator, &Generator::finished, this, &Controller::generatorFinished);
    m_generator->generate();
}

int Controller::loadIconRepository(QString path, int size)
{
    if (m_repository != nullptr) {
        delete m_repository;
    }
    m_repository = new IconRepository(path, size);
    return m_repository->icons().size();
}

void Controller::setSourceImage(QString path)
{
    if (m_repository != nullptr) {
        delete m_sourceImage;
    }
    m_sourceImage = new QImage(path);
}

QImage Controller::mosaic()
{
    return m_generator->mosaic()->toImage();
}

int Controller::maxProgress()
{
    return m_generator->maxProgress();
}

void Controller::setThreadCount(int n)
{
    m_threadCount = n;
}

void Controller::setRandomness(int n)
{
    if (n > m_repository->icons().size()) {
        n = m_repository->icons().size();
    }
    m_randomness = n;
}

void Controller::setImageBlockSize(int px)
{
    m_imageBlockSize = px;
}

}