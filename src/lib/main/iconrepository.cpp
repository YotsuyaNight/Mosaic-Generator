#include "iconrepository.h"
#include "pixelmap.h"
#include <QDir>
#include <QDebug>

namespace MosaicGenerator {

IconRepository::IconRepository(QString path) 
{
    QDir directory(path);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    directory.setNameFilters(filters);

    for (QFileInfo file : directory.entryInfoList()) {
        QImage *image = new QImage(file.absoluteFilePath());
        PixelMap *pm = new PixelMap(*image);
        m_images.append(pm);
        delete image;
    }
}

IconRepository::~IconRepository()
{
    qDeleteAll(m_images);
}

}
