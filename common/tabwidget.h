#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "listwidget.h"
#include "qpushbutton.h"
#include <QWidget>

namespace Ui {
class TabWidget;
}
class TabWidgetP;
class TabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();
    void addTab(QPushButton *button, ListWidget *widget, QString name);
    void removeTab(QString name);
    void clear();

private:
    Ui::TabWidget *ui;
    TabWidgetP * const p;
};

#endif // TABWIDGET_H
