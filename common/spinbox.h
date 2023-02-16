#ifndef SPINBOX_H
#define SPINBOX_H

#include <QSpinBox>

class SpinBox : public QSpinBox
{
public:
    SpinBox(QWidget *parent = nullptr);
    void reSetNumber();
    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // SPINBOX_H
