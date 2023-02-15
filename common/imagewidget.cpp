#include "imagewidget.h"
#include "ui_imagewidget.h"
#include "common.h"
ImageWidget::ImageWidget(QWidget *parent, QByteArray data, QString title, int size) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    ui->label->setPixmap(Common::creatImage(data));
    ui->label->setScaledContents(true);
    this->setWindowTitle(title);
    this->setMaximumSize(QSize(size, size));
    this->setMinimumSize(QSize(size, size));
}

ImageWidget::~ImageWidget()
{
    delete ui;
}
