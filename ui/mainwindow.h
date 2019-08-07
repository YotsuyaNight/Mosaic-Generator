#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

namespace MosaicGenerator {

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

private slots:
    void chooseImage();
    void chooseIconDirectory();
    void generate();
    void checkFieldsValid();
    void generatorFinished();
    void updateProgress(int progress);

private:
    void setUiEnabled(bool enabled);

};

}

#endif