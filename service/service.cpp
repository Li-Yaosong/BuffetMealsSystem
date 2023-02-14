#include "service.h"
#include "QSqlDatabase"
#include "QDebug"
#include <QFileDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
Service::Service(QObject *parent)
    : ServiceSimpleSource(parent)
{
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

Service::~Service()
{

}

void Service::addDishes(const QMap<QString, QByteArray> &map)
{
    QSqlQuery query;
    query.prepare("insert into menu(name,number,price,image,storage) values(:name,:number,:price,:image,:storage)");
    QStringList keyList = map.keys();
    for(QString key : keyList)
    {
        if(key == "number")
        {
            query.bindValue(":" + key,map.value(key).toInt());
        }
        else if(key == "price")
        {
            query.bindValue(":" + key, map.value(key).toDouble());
        }
        else if(key == "image")
        {
            query.bindValue(":" + key, map.value(key));
        }
        else
        {
            query.bindValue(":" + key, QString(map.value(key)));
        }
    }

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

void Service::delDishes(const QStringList &delList)
{
    QSqlQuery query;
    for(const QString &name : delList)
    {
        query.prepare(QString("delete from menu where name='%1'").arg(name));
        if(!query.exec())
        {
            qDebug() << "del error";
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            qDebug() << "del ok";
        }
    }

}

QByteArray Service::getAllDishes()
{
        QMap<int, QMap<QString, QVariant>> Allmap;
        QSqlQuery query;
        QString select = "select * from menu";
        query.exec(select);

        while( query.next() )
        {
            QMap<QString, QVariant> map;
            map.insert("name", query.value(0));
            map.insert("number", query.value(1));
            map.insert("price", query.value(2).toDouble());
            map.insert("image", query.value(3).toByteArray());
            map.insert("storage", query.value(4).toByteArray());
            //        qDebug()<<data;
            //        QPixmap photo;
            //        photo.loadFromData(data, "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
            //        ui->label->setPixmap(photo);
            //        ui->label->setScaledContents(true);
            Allmap.insert(query.value(1).toInt(),map);
        }
        QByteArray byte;
        QDataStream Data(&byte,QIODevice::WriteOnly);
        Data << Allmap;
        return byte;
}

QByteArray Service::showImage()
{
    QSqlQuery query;
    QString select = "select * from menu";
    query.exec(select);

    if( query.next() )
    {
        QByteArray data = query.value(3).toByteArray();
            return data;
//        qDebug()<<data;
//        QPixmap photo;
//        photo.loadFromData(data, "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
//        ui->label->setPixmap(photo);
//        ui->label->setScaledContents(true);
    }
    return QByteArray();
}
