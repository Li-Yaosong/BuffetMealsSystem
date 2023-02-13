#include "service.h"
#include "ui_service.h"
#include "QSqlDatabase"
#include "QDebug"
#include <QFileDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");  //连接本地主机
    db.setPort(3306);
    db.setDatabaseName("ordering_system");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    qDebug()<< ok;
    showImage();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addDishes()
{
    QSqlQuery query;
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.jpg)"));
    QByteArray data;
    QFile* file=new QFile(imagePath); //file为二进制数据文件名
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();
    qDebug()<<data;
    QVariant var(data);
    query.prepare("insert into menu(name,number,price,image,storage) values(:name,:number,:price,:image,:storage)");
    query.bindValue(":name","test");
    query.bindValue(":number",0);
    query.bindValue(":price",10);
    query.bindValue(":image",data);
    query.bindValue(":storage","yes");
    if(!query.exec())
        {
            qDebug() << "insert error";
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            qDebug() << "insert ok";
    }
}

void Widget::showImage()
{
    QSqlQuery query;
    QString select = "select * from menu";
    query.exec(select);

    if( query.next() )
    {
        QByteArray data = query.value(3).toByteArray();
        qDebug()<<data;
        QPixmap photo;
        photo.loadFromData(data, "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
        ui->label->setPixmap(photo);
        ui->label->setScaledContents(true);
    }
}
