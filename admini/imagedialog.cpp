#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent, QByteArray data) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    QPixmap photo;
    photo.loadFromData(data, "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
    ui->label->setPixmap(photo);
    ui->label->setScaledContents(true);
}

ImageDialog::~ImageDialog()
{
    delete ui;
}
