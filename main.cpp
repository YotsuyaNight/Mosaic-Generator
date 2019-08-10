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

#include <QApplication>
#include <QMainWindow>
#include <ctime>
#include <cstdlib>
#include "iconrepository.h"
#include "mainwindow.h"
#include "controller.h"

int main(int argc, char **argv)
{
    std::srand(std::time(nullptr));

    QApplication app(argc, argv);

    MosaicGenerator::MainWindow mw;
    mw.show();

    int status = app.exec();

    delete MosaicGenerator::Controller::self();
    return status;
}