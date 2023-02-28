#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include "libbms_global.h"

namespace Ui {
class ListWidget;
}

class DishWidget;
class ListWidgetP;
class LIBBMS_EXPORT ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(int head = true, QWidget *parent = nullptr);
    ~ListWidget();

    void addDishWidget(QWidget *widgit);

    void clear();
    void showTopCheckBox();
    void hideTopCheckBox();

private:
    Ui::ListWidget *ui;
    ListWidgetP * const p;
};

#endif // LISTWIDGET_H
