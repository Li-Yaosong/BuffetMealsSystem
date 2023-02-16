#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent)
{

}

void SpinBox::reSetNumber()
{
    this->setValue(0);
}
void SpinBox::wheelEvent(QWheelEvent *event)
{
    return;
}
