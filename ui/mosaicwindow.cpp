#include "mosaicwindow.h"
#include "controller.h"
#include <QFileDialog>

namespace MosaicGenerator {

MosaicWindow::MosaicWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    connect(buttonSaveAs, &QPushButton::clicked, this, &MosaicWindow::saveAs);
    m_mosaic = Controller::self()->mosaic();
}

void MosaicWindow::open()
{
    QImage scaled = m_mosaic.scaled(imageLabel->size(), Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(scaled);
    imageLabel->setPixmap(pixmap);
    show();
}

void MosaicWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDefaultSuffix(QStringLiteral("png"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec()) {
        QString file = dialog.selectedFiles()[0];
        m_mosaic.save(file);
    }
}

}