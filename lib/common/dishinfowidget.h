#ifndef DISHINFOWIDGET_H
#define DISHINFOWIDGET_H

#include <QWidget>
#include <QMap>
//#include "libbms_global.h"
#include "global.h"

namespace Ui {
class DishInfoWidget;
}

class  DishInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DishInfoWidget(Dish dishInfo = Dish(), QWidget *parent = nullptr);
    ~DishInfoWidget();
    Dish info();
signals:
    void infoChanged(Dish);
private slots:
    void on_pushButton_browse_clicked();
    void textChanged();
private:
    void initStyle();
    void init();
    Ui::DishInfoWidget *ui;
    Dish m_info;
};

#endif // DISHINFOWIDGET_H
