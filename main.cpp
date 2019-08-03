#include <QApplication>
#include "mainwindow.h"
#include "iconrepository.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    MosaicGenerator::MainWindow window;
    window.show();

    MosaicGenerator::IconRepository ir("/home/yotsuya/icons");

    return app.exec();
}