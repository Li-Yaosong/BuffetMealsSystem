#include "imagewidget.h"
#include "ui_imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent, QByteArray data) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    this->hide();
    QPixmap photo;
    photo.loadFromData(data, "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
    ui->label->setPixmap(photo);
    ui->label->setScaledContents(true);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}
