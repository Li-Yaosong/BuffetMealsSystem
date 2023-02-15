#ifndef CDISHWIDGET_H
#define CDISHWIDGET_H

#include "common.h"
#include <QWidget>
#include <QVariant>
namespace Ui {
class CDishWidget;
}
class ImageWidget;
class CDishWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDishWidget(QWidget *parent = nullptr, Common::Dish dishIfon ={});
    ~CDishWidget();
    void creatButton();

private:
    Ui::CDishWidget *ui;
    Common::Dish m_dishInfo;
    ImageWidget *m_image;
};

#endif // CDISHWIDGET_H
