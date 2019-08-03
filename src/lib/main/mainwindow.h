#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ui_mainwindow.h"

namespace MosaicGenerator {

class MainWindow : public QWidget, public Ui::MainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() override;

private:
};

}

#endif
