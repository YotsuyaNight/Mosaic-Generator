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

namespace MosaicGenerator {

MainWindow::MainWindow()
{
    setupUi(this);
    warningIconSettingsChanged->hide();
    buttonAbort->hide();

    connect(buttonIconDirPath, &QPushButton::clicked, this, &MainWindow::chooseIconDirectory);
    connect(buttonImagePath, &QPushButton::clicked, this, &MainWindow::chooseImage);
    connect(buttonLoadIcons, &QPushButton::clicked, this, &MainWindow::loadIconDirectory);
    connect(buttonGenerate, &QPushButton::clicked, this, &MainWindow::generate);
    connect(buttonAbort, &QPushButton::clicked, this, &MainWindow::abort);
    connect(iconDirPath, &QLineEdit::textChanged, this, &MainWindow::displayIconSettingsWarning);
    connect(iconLength, QOverload<const QString &>::of(&QSpinBox::valueChanged), this, &MainWindow::displayIconSettingsWarning);
    connect(Controller::self(), &Controller::generatorProgress, this, &MainWindow::updateProgress);
    connect(Controller::self(), &Controller::generatorFinished, this, &MainWindow::generatorFinished);

    threadCount->setValue(QThread::idealThreadCount() / 2);
    threadCount->setMaximum(QThread::idealThreadCount());

    setFocus();
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
    }
}

void MainWindow::loadIconDirectory()
{
    int iconsLoaded = Controller::self()->loadIconRepository(iconDirPath->text(), iconLength->value());
    if (iconsLoaded > 0) {
        loadedIconsCount->setText("Detected " + QString::number(iconsLoaded) + " images in specified directory.");
        m_validRepository = true;
        warningIconSettingsChanged->hide();
    } else {
        loadedIconsCount->setText("No images detected in specified directory!");
        m_validRepository = false;
    }
    checkSettings();
}

void MainWindow::generate()
{
    progressBar->setValue(0);
    Controller::self()->setThreadCount(threadCount->value());
    Controller::self()->setRandomness(randomness->value());
    Controller::self()->setImageBlockSize(imageBlockSize->value());
    Controller::self()->setSourceImage(imagePath->text());
    Controller::self()->startGenerator();
    setUiEnabled(false);
    progressBar->setMaximum(Controller::self()->maxProgress());
    buttonGenerate->hide();
    buttonAbort->show();
}

void MainWindow::abort()
{
    Controller::self()->abortGenerator();
    buttonGenerate->show();
    buttonAbort->hide();
    setUiEnabled(true);
    progressBar->setValue(0);
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
    buttonGenerate->show();
    buttonAbort->hide();
    MosaicWindow *window = new MosaicWindow;
    window->open();
}

void MainWindow::setUiEnabled(bool enabled)
{
    iconDirPath->setEnabled(enabled);
    buttonIconDirPath->setEnabled(enabled);
    imagePath->setEnabled(enabled);
    buttonImagePath->setEnabled(enabled);
    buttonLoadIcons->setEnabled(enabled);
    randomness->setEnabled(enabled);
    iconLength->setEnabled(enabled);
    threadCount->setEnabled(enabled);
    imageBlockSize->setEnabled(enabled);
}

void MainWindow::updateProgress(int progress)
{
    progressBar->setValue(progress);
}

void MainWindow::displayIconSettingsWarning(QString val)
{
    Q_UNUSED(val);
    if (m_validRepository) {
        warningIconSettingsChanged->show();
    }
}

}
