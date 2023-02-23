#include "dishesedict.h"
#include "ui_dishesedict.h"
#include <QLabel>
#include "common.h"
#include "imagewidget.h"
#include "titalwidget.h"
#include "dishinfowidget.h"
DishesEdict::DishesEdict(QWidget *parent, QByteArray data) :
    QWidget(parent),
    ui(new Ui::DishesEdict)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this,QString::fromLocal8Bit("编辑"), false);
    ui->verticalLayout->insertWidget(0, tital);
    ImageWidget *image = new ImageWidget(this, data,"",300);
    ui->horizontalLayout->insertWidget(0, image);
    DishInfoWidget *infoWidget = new DishInfoWidget();
    ui->horizontalLayout->insertWidget(1, infoWidget);
    resize(700,400);
}

DishesEdict::~DishesEdict()
{
    delete ui;
}
