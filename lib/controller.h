#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QImage;

namespace MosaicGenerator {

class Generator;
class IconRepository;

class Controller : public QObject
{
    Q_OBJECT

public:
    ~Controller();
    static Controller* self();

    void startGenerator();
    void setIconRepository(IconRepository *repository);
    void setSourceImage(QImage *image);
    void setThreadCount(int n);
    void setTileWidth(int px);
    void setTileHeight(int px);
    QImage mosaic();
    int maxProgress();

signals:
    void generatorFinished();
    void generatorProgress(int progress);

private:
    Controller();

    inline static Controller *m_self = nullptr;
    IconRepository *m_repository = nullptr;
    Generator *m_generator = nullptr;
    QImage *m_sourceImage = nullptr;
    int m_threadCount;
    int m_tw = 1;
    int m_th = 1;
};

}

#endif
