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

#ifndef MOSAICWINDOW_H
#define MOSAICWINDOW_H

#include "ui_mosaicwindow.h"

class QGraphicsView;
class QMessageBox;

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
    QGraphicsView *imageView;
    QImage m_mosaic;
    QMessageBox *m_savingDialog;

};

class SaveImageJob : public QObject
{
    Q_OBJECT

public:
    SaveImageJob(QImage &image, QString path);

public slots:
    void process();

signals:
    void finished();

private:
    QImage &m_image;
    QString m_path;

};

}

#endif
