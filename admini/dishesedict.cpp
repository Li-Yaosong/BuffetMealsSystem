#include "dishesedict.h"
#include "ui_dishesedict.h"
#include <QLabel>
#include "common.h"
#include "imagewidget.h"
DishesEdict::DishesEdict(QWidget *parent, QByteArray data) :
    QWidget(parent),
    ui(new Ui::DishesEdict)
{
    ui->setupUi(this);
    ImageWidget *image = new ImageWidget(this, data);
    ui->verticalLayout->insertWidget(0, image);
//    ui->label->setPixmap(Common::creatImage(data));
//    ui->label->setScaledContents(true);
}

DishesEdict::~DishesEdict()
{
    delete ui;
}
