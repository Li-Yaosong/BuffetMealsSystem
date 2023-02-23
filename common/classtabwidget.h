#ifndef CLASSTABWIDGET_H
#define CLASSTABWIDGET_H

#include "dishlistwidget.h"
#include "qpushbutton.h"
#include <QWidget>

namespace Ui {
class ClassTabWidget;
}
class ClassTabWidgetP;
class ClassTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassTabWidget(QWidget *parent = nullptr);
    ~ClassTabWidget();
    void addTab(QPushButton *button, DishListWidget *widget, QString name);
    void removeTab(QString name);
    void clear();

private:
    Ui::ClassTabWidget *ui;
    ClassTabWidgetP * const p;
};

#endif // CLASSTABWIDGET_H
