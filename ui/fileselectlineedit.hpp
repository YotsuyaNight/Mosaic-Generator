#ifndef FILESELECTLINEEDIT_H
#define FILESELECTLINEEDIT_H

#include <QLineEdit>

namespace MosaicGenerator {

class FileSelectLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FileSelectLineEdit(QWidget *parent = nullptr)
        : QLineEdit(parent)
    {
        setReadOnly(true);
        setPlaceholderText("Click to choose...");
    }

    virtual void mousePressEvent(QMouseEvent *event) override
    {
        emit clicked();
    }

signals:
    void clicked();
};

}

#endif
