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

#include "mainwindow.h"
#include "mosaicwindow.h"
#include "controller.h"
#include "iconrepository.h"
#include "generator.h"
#include <QFileDialog>
#include <QThread>
#include <QDebug>

namespace MosaicGenerator {

MainWindow::MainWindow()
{
    setupUi(this);

    connect(buttonChooseIconDir, &QPushButton::clicked, this, &MainWindow::chooseIconDirectory);
    connect(buttonChooseImage, &QPushButton::clicked, this, &MainWindow::chooseImage);
    connect(buttonGenerate, &QPushButton::clicked, this, &MainWindow::generate);
    connect(Controller::self(), &Controller::generatorProgress, this, &MainWindow::updateProgress);
    connect(Controller::self(), &Controller::generatorFinished, this, &MainWindow::generatorFinished);

    threadCount->setValue(QThread::idealThreadCount() / 2);
    threadCount->setMaximum(QThread::idealThreadCount());

    setFocus();
}

MainWindow::~MainWindow()
{
    for (MosaicWindow *window : m_mosaicWindows) {
        delete window;
    }
}

void MainWindow::chooseImage()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec()) {
        QString file = dialog.selectedFiles()[0];
        imagePath->setText(file);
    }
    checkSettings();
}

void MainWindow::chooseIconDirectory()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    if (dialog.exec()) {
        QString file = dialog.selectedFiles()[0];
        iconDirPath->setText(file);
        int iconsLoaded = Controller::self()->loadIconRepository(file);
        if (iconsLoaded > 0) {
            loadedIconsCount->setText("Detected " + QString::number(iconsLoaded) + " images in specified directory.");
            m_validRepository = true;
        } else {
            loadedIconsCount->setText("No images detected in specified directory!");
            m_validRepository = false;
        }
    }
    checkSettings();
}

void MainWindow::generate()
{
    progressBar->setValue(0);

    qDebug() << "Generator starting with parameters:";
    qDebug() << "Icon repository path:" << iconDirPath->text();
    qDebug() << "Source image path:" << imagePath->text();
    qDebug() << "Randomness:" << randomness->value();
    qDebug() << "Icon size:" << iconLength->value();
    qDebug() << "Threads count:" << threadCount->value();

    Controller::self()->setThreadCount(threadCount->value());
    Controller::self()->setRandomness(randomness->value());
    Controller::self()->setIconSize(iconLength->value());
    Controller::self()->setImageBlockSize(imageBlockSize->value());
    Controller::self()->setSourceImage(imagePath->text());
    Controller::self()->startGenerator();
    setUiEnabled(false);

    progressBar->setMaximum(Controller::self()->maxProgress());
}

void MainWindow::checkSettings()
{
    if (!imagePath->text().isEmpty() && m_validRepository)
    {
        buttonGenerate->setEnabled(true);
    } else {
        buttonGenerate->setEnabled(false);
    }
}

void MainWindow::generatorFinished()
{
    progressBar->setValue(Controller::self()->maxProgress());
    setUiEnabled(true);
    MosaicWindow *window = new MosaicWindow;
    m_mosaicWindows.append(window);
    window->open();
}

void MainWindow::setUiEnabled(bool enabled)
{
    buttonChooseIconDir->setEnabled(enabled);
    buttonChooseImage->setEnabled(enabled);
    buttonGenerate->setEnabled(enabled);
    randomness->setEnabled(enabled);
    iconLength->setEnabled(enabled);
    threadCount->setEnabled(enabled);
    imageBlockSize->setEnabled(enabled);
}

void MainWindow::updateProgress(int progress)
{
    progressBar->setValue(progress);
}

}
