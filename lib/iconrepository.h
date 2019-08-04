#ifndef ICONREPOSITORY_H
#define ICONREPOSITORY_H

#include <QString>
#include <QImage>

namespace MosaicGenerator {

class PixelMap;

class IconRepository
{
public:
    explicit IconRepository(QString path);
    virtual ~IconRepository();

    QVector<PixelMap*> icons();

private:
    QVector<PixelMap*> m_icons;
};

}

#endif
