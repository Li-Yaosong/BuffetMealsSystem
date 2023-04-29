#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>

namespace Ui {
class RegistWidget;
}

class RegistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistWidget(QWidget *parent = nullptr);
    ~RegistWidget();

    void initStyle();

private:
    Ui::RegistWidget *ui;
};

#endif // REGISTWIDGET_H
