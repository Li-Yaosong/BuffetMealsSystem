#ifndef DISHWIDGET_H
#define DISHWIDGET_H

#include <QWidget>
#include <QVariant>
#include "global.h"
namespace Ui {
class DishWidget;
}
class DishesEdict;
class DishWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DishWidget(QWidget *parent = nullptr, Dish dishInfo =Dish());
    ~DishWidget();
    void setClass(const QString &num);
    void setName(const QString &name);
    void setPrice(const double &price);
    void setStorage(const int &storage);
    void showCheckBox();
    void hideCheckBox();

signals:
    void checkBoxStateChanged(QString name, bool del);
    void edictFinished();
private slots:
    void on_pushButton_clicked();
private:
    Ui::DishWidget *ui;
    DishesEdict *m_imageW;
    Dish m_dishInfo;
};

#endif // DISHWIDGET_H
