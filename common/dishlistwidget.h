#ifndef DISHLISTWIDGET_H
#define DISHLISTWIDGET_H

#include <QWidget>

namespace Ui {
class DishListWidget;
}

class DishWidget;
class DishListWidgetP;
class DishListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DishListWidget(bool head = true, QWidget *parent = nullptr);
    ~DishListWidget();

    void addDishWidget(QWidget *widgit);

    void clear();
    void showTopCheckBox();
    void hideTopCheckBox();

private:
    Ui::DishListWidget *ui;
    DishListWidgetP * const p;
};

#endif // DISHLISTWIDGET_H
