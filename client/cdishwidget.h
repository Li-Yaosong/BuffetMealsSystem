﻿#ifndef CDISHWIDGET_H
#define CDISHWIDGET_H

#include "common.h"
#include <QWidget>
#include <QVariant>
#include "spinbox.h"
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
public slots:
    void reSetNumber();
private:
    Ui::CDishWidget *ui;
    Common::Dish m_dishInfo;
    ImageWidget *m_image;
    SpinBox *m_spinBox;
};

#endif // CDISHWIDGET_H
