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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

namespace MosaicGenerator {

class MosaicWindow;
class FileSelectLineEdit;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

private slots:
    void chooseImage();
    void chooseIconDirectory();
    void loadIconDirectory();
    void generate();
    void checkSettings();
    void generatorFinished();
    void updateProgress(int progress);
    void displayIconSettingsWarning(QString val);

private:
    void setUiEnabled(bool enabled);

    FileSelectLineEdit *iconDirPath;
    FileSelectLineEdit *imagePath;
    bool m_validRepository = false;

};

}

#endif