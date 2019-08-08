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