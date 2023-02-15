#include "imagewidget.h"
#include "ui_imagewidget.h"
#include <QLabel>
#include "common.h"
ImageWidget::ImageWidget(QWidget *parent, QByteArray data) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    ui->label->setPixmap(Common::creatImage(data));
    ui->label->setScaledContents(true);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}
