#include "iconrepository.h"
#include "pixelmap.h"
#include <QDir>
#include <QDebug>

namespace MosaicGenerator {

IconRepository::IconRepository(QString path) 
{
    //Scan directory for image files
    QDir directory(path);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    directory.setNameFilters(filters);
    //Turn images into PixelMap objects
    for (QFileInfo file : directory.entryInfoList()) {
        QImage *image = new QImage(file.absoluteFilePath());
        PixelMap *pm = new PixelMap(*image);
        m_icons.append(pm);
        delete image;
    }
}

IconRepository::~IconRepository()
{
    qDeleteAll(m_icons);
}

QVector<PixelMap*> IconRepository::icons()
{
    return m_icons;
}

}
