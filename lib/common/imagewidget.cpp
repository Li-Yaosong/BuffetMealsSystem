#include "imagewidget.h"
#include "ui_imagewidget.h"
#include "common.h"
#include "stylesheet.h"
#include <QStyleOption>
#include <QPainter>
#include <QBitmap>
ImageWidget::ImageWidget(QWidget *parent, QByteArray data, QString title, int size) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    m_image = Common::creatImage(data);
//    ui->label->setPixmap(Common::creatImage(data));
//    ui->label->setScaledContents(true);
    this->setWindowTitle(title);
    this->setMaximumSize(QSize(size, size));
    this->setMinimumSize(QSize(size, size));
//    this->setStyleSheet(StyleSheet::widgetStyle());
    ui->label->setStyleSheet("border:15px solid rgb(255,202,24);"
                             "border-radius:50px;"
                             "background-color: rgba(255,0,0,0);");
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{

    //绘制样式
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);//绘制样式

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter painter(&bmp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    //此处可修改圆角矩形大小，也可以绘制为其他想要的形状，比如圆形
    painter.drawRoundedRect(bmp.rect(), 55, 55);
    //painter.drawEllipse(bmp.rect());绘制圆或椭圆
    //该函数便使得QBitmap上像素为1的区域才显示出来
    setMask(bmp);

    //QPainter p(this);

    //此处背景图可自由设置
    p.drawPixmap(0, 0, this->width(), this->height(), m_image);
}
