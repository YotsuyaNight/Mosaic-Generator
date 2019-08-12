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

#include "mosaicwindow.h"
#include "controller.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QThread>

namespace MosaicGenerator {

class ZoomGraphicsView : public QGraphicsView
{
public:
    ZoomGraphicsView(QWidget *parent = nullptr)
        : QGraphicsView(parent)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

protected:
    void wheelEvent(QWheelEvent *event)
    {
        if (event->delta() > 0) {
            scale(1.2, 1.2);
        } else {
            scale(0.8, 0.8);
        }
    }
};

SaveImageJob::SaveImageJob(QImage &image, QString path)
    : m_image(image), m_path(path)
{
}

void SaveImageJob::process()
{
    m_image.save(m_path);
    emit finished();
}

MosaicWindow::MosaicWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    m_mosaic = Controller::self()->mosaic();
    connect(buttonSaveAs, &QPushButton::clicked, this, &MosaicWindow::saveAs);

    m_savingDialog = new QMessageBox(this);
    m_savingDialog->setWindowTitle("Mosaic Generator");
    m_savingDialog->setText("Saving image, please wait...");
    m_savingDialog->setIcon(QMessageBox::Information);
    m_savingDialog->setStandardButtons(0);

    imageView = new ZoomGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene(imageView);
    imageView->setScene(scene);
    windowLayout->insertWidget(0, imageView);
    imageView->show();
}

void MosaicWindow::open()
{
    QPixmap pixmap = QPixmap::fromImage(m_mosaic);
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    imageView->scene()->addItem(pixmapItem);
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
        QThread *thread = new QThread;
        SaveImageJob *save = new SaveImageJob(m_mosaic, file);
        save->moveToThread(thread);
        connect(thread, &QThread::started, save, &SaveImageJob::process);
        connect(save, &SaveImageJob::finished, thread, &QThread::quit);
        connect(save, &SaveImageJob::finished, save, &SaveImageJob::deleteLater);
        connect(thread, &QThread::finished, m_savingDialog, &QDialog::accept);
        connect(thread, &QThread::finished, save, &QThread::deleteLater);
        thread->start();
        m_savingDialog->exec();
    }
}

}