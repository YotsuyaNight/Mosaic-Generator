#ifndef MOSAICWINDOW_H
#define MOSAICWINDOW_H

#include "ui_mosaicwindow.h"

namespace MosaicGenerator {

class MosaicWindow : public QWidget, public Ui::MosaicWindow
{
    Q_OBJECT

public:
    explicit MosaicWindow(QWidget *parent = nullptr);

    void open();

private slots:
    void saveAs();

private:
    QImage m_mosaic;

};

}

#endif
