#ifndef CLASSBUTTON_H
#define CLASSBUTTON_H

#include "qicon.h"
#include <QWidget>

namespace Ui {
class ClassButton;
}
class QPushButton;
class ClassButton : public QWidget
{
    Q_OBJECT

public:
    explicit ClassButton(QString name, QIcon icon,QWidget *parent = nullptr);
    ~ClassButton();
    QPushButton * button();

private:
    Ui::ClassButton *ui;
};

#endif // CLASSBUTTON_H
