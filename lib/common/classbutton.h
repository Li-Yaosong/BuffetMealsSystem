#ifndef CLASSBUTTON_H
#define CLASSBUTTON_H
#include "libbms_global.h"
#include "qicon.h"
#include <QWidget>

namespace Ui {
class ClassButton;
}
class QPushButton;
class LIBBMS_EXPORT ClassButton : public QWidget
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
