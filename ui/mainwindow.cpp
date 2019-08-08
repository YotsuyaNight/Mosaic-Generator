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
    checkFieldsValid();
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
    checkFieldsValid();
}

void MainWindow::generate()
{
    progressBar->setValue(0);

    IconRepository *ir = new IconRepository(iconDirPath->text());
    QImage *img = new QImage(imagePath->text());

    qDebug() << "Generator starting with parameters:";
    qDebug() << "Icon repository path:" << iconDirPath->text();
    qDebug() << "Source image path:" << imagePath->text();
    qDebug() << "Uniqueness:" << uniqueness->value();
    qDebug() << "Tile size:" << iconSideLength->value();
    qDebug() << "Threads count:" << threadCount->value();

    Controller::self()->setIconRepository(ir);
    Controller::self()->setSourceImage(img);
    Controller::self()->setThreadCount(threadCount->value());
    Controller::self()->setTileWidth(iconSideLength->value());
    Controller::self()->setTileHeight(iconSideLength->value());
    Controller::self()->startGenerator();
    setUiEnabled(false);

    progressBar->setMaximum(Controller::self()->maxProgress());
}

void MainWindow::checkFieldsValid()
{
    if (!imagePath->text().isEmpty() &&
        !iconDirPath->text().isEmpty())
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
    uniqueness->setEnabled(enabled);
    iconSideLength->setEnabled(enabled);
    threadCount->setEnabled(enabled);
}

void MainWindow::updateProgress(int progress)
{
    progressBar->setValue(progress);
}

}
