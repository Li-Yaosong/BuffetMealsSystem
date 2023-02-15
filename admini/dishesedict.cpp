#include "dishesedict.h"
#include "ui_dishesedict.h"
#include <QLabel>
#include "common.h"
DishesEdict::DishesEdict(QWidget *parent, QByteArray data) :
    QWidget(parent),
    ui(new Ui::DishesEdict)
{
    ui->setupUi(this);
    ui->label->setPixmap(Common::creatImage(data));
    ui->label->setScaledContents(true);
}

DishesEdict::~DishesEdict()
{
    delete ui;
}
