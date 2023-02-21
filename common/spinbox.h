#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>
#include <QSpinBox>
namespace Ui {
class SpinBox;
}
class SpinBoxP;
class SpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit SpinBox(QWidget *parent = nullptr, bool doubleSpin = false);
    ~SpinBox();

    void reSetValue();
    double value();
signals:
    void valueChange(double);
    void valueChange(int);


private:
    Ui::SpinBox *ui;
    SpinBoxP * const p;
};

#endif // SPINBOX_H
