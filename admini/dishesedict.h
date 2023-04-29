#ifndef DISHESEDICT_H
#define DISHESEDICT_H

#include <QWidget>
#include "global.h"

namespace Ui {
class DishesEdict;
}
class DishInfoWidget;
class ImageWidget;
class DishesEdict : public QWidget
{
    Q_OBJECT

public:
    explicit DishesEdict(Dish dishInfo = Dish(), QWidget *parent = nullptr);
    ~DishesEdict();
    Dish dishInfo();
signals:
    void edictFinished(Dish);
public slots:
    void dishInfoChanged(Dish dishInfo);
private slots:
    void on_pushButton_finished_clicked();

    void on_pushButton_clicked();

private:
    Ui::DishesEdict *ui;
    DishInfoWidget *m_infoWidget;
    ImageWidget *m_image;
    Dish m_dishInfo;
    QString old;
};

#endif // DISHESEDICT_H
