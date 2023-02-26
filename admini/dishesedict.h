#ifndef DISHESEDICT_H
#define DISHESEDICT_H

#include <QWidget>

namespace Ui {
class DishesEdict;
}

class DishesEdict : public QWidget
{
    Q_OBJECT

public:
    explicit DishesEdict(QWidget *parent = nullptr, QByteArray data = QByteArray());
    ~DishesEdict();

private:
    Ui::DishesEdict *ui;
};

#endif // DISHESEDICT_H
