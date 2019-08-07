#include <QApplication>
#include <QMainWindow>
#include "iconrepository.h"
#include "mainwindow.h"
#include "controller.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MosaicGenerator::MainWindow mw;
    mw.show();

    int status = app.exec();

    delete MosaicGenerator::Controller::self();
    return status;
}