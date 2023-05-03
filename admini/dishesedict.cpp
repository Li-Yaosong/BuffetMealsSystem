#include "dishesedict.h"
#include "ui_dishesedict.h"
#include <QLabel>

#include "imagewidget.h"
#include "titalwidget.h"
#include "dishinfowidget.h"
#include "common.h"
#include "stylesheet.h"
DishesEdict::DishesEdict(Dish dishInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishesEdict),
    m_infoWidget(new DishInfoWidget(dishInfo)),
    m_image(new ImageWidget(this, dishInfo.image,"",300)),
    m_dishInfo(dishInfo),
    old(dishInfo.name)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this,QString::fromLocal8Bit("编辑"), false);
    ui->verticalLayout->insertWidget(0, tital);
    ui->horizontalLayout->insertWidget(0, m_image);
    ui->horizontalLayout->insertWidget(1, m_infoWidget);
    connect(m_infoWidget, &DishInfoWidget::infoChanged, this, &DishesEdict::dishInfoChanged);
    ui->pushButton_finished->setEnabled(false);
    m_infoWidget->setEnabled(false);
    resize(700,400);
    ui->pushButton_finished->setStyleSheet(StyleSheet::buttonStyle(1));
    ui->pushButton->setStyleSheet(StyleSheet::buttonStyle(1));
}

DishesEdict::~DishesEdict()
{
    delete ui;
}

Dish DishesEdict::dishInfo()
{
    Dish dishInfo;
    return dishInfo;
}

void DishesEdict::dishInfoChanged(Dish dishInfo)
{
    QByteArray image = m_dishInfo.image;
    m_dishInfo = dishInfo;
    if(!dishInfo.image.isEmpty())
    {
        m_image->updateImage(m_dishInfo.image);
    }
    else
    {
        m_dishInfo.image = image;
    }
    ui->pushButton_finished->setEnabled(!dishInfo.name.isEmpty());
}

void DishesEdict::on_pushButton_finished_clicked()
{
    Service->rep()->modifiDishe(m_dishInfo, old);
    this->hide();
    emit edictFinished(m_dishInfo);
}


void DishesEdict::on_pushButton_clicked()
{
    ui->pushButton_finished->setEnabled(true);
    m_infoWidget->setEnabled(true);
    ui->pushButton->setEnabled(false);
}

