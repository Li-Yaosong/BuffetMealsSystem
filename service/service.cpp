﻿#include "service.h"
#include "QSqlDatabase"
#include "QDebug"
#include <QFileDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QList>
#include <QMultiMap>
#include "console.h"
Service::Service(QObject *parent)
    : ServiceSimpleSource(parent),
      m_console(new Console)
{
    m_console->show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    for(const QString &name : QSqlDatabase::drivers())
    {
        m_console->appendDebug(name);
    }

    db.setHostName("localhost");  //连接本地主机
    db.setPort(3306);
    db.setDatabaseName("ordering_system");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if(ok)
    {
        m_console->appendDebug("true");
    }
    else
    {
        m_console->appendDebug("false");
    }
    qDebug()<< ok;
    showImage();
}

Service::~Service()
{

}

void Service::addClass(const QMap<QString, QByteArray> &map)
{
    QSqlQuery query;
    query.prepare("insert into menu_classification(class_name,image) values(:class_name,:image)");
    QStringList keyList = map.keys();
    for(const QString &key : keyList)
    {
        query.bindValue(":" + key, QString(map.value(key)));
    }

    if(!query.exec())
        {
            m_console->appendDebug("insert error");
            qDebug() << "insert error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            qDebug() << "insert class ok";
    }
}

void Service::delClass(const QStringList &delList)
{
    QSqlQuery query;
    for(const QString &name : delList)
    {
        query.prepare(QString("delete from menu where class='%1'").arg(name));
        if(!query.exec())
        {
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del ok");
            qDebug() << "del ok";
        }
        query.prepare(QString("delete from menu_classification where class_name='%1'").arg(name));
        if(!query.exec())
        {
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del class ok");
            qDebug() << "del class ok";
        }
    }
}

void Service::addDishes(const QMap<QString, QByteArray> &map)
{
    QSqlQuery query;
    query.prepare("insert into menu(name,class,price,image,storage) values(:name,:class,:price,:image,:storage)");
    QStringList keyList = map.keys();
    for(const QString &key : keyList)
    {
        if(key == "price")
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
            m_console->appendDebug("insert error");
            qDebug() << "insert error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("insert dishes ok");
            qDebug() << "insert dishes ok";
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
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del ok");
            qDebug() << "del ok";
        }
    }

}

QByteArray Service::getAllClass()
{
    QMap<QString, QVariant> map;
    QSqlQuery query;
    QString select = "select * from menu_classification";
    query.exec(select);
    while( query.next() )
    {
        map.insert(query.value(0).toString(), query.value(1).toByteArray());
    }
    QByteArray byte;
    QDataStream Data(&byte,QIODevice::WriteOnly);
    Data << map;
    return byte;
}

QByteArray Service::getAllDishes()
{
    QMultiMap <QString, QMap<QString, QVariant>>Allmap;
//    QMap<QString, QList<QMap<QString, QVariant>> > Allmap;
    QSqlQuery query;
//    query.exec("select * from menu_classification");
//    while( query.next() )
//    {
//        QList<QMap<QString, QVariant>> list={};
//        Allmap.insert(query.value(0).toString(),list);
//    }
    query.exec("select * from menu");

    while( query.next() )
    {
        QMap<QString, QVariant> map;
        map.insert("name", query.value(0));
        map.insert("class", query.value(1));
        map.insert("price", query.value(2).toDouble());
        map.insert("image", query.value(3).toByteArray());
        map.insert("storage", query.value(4).toByteArray());
        Allmap.insert(query.value(1).toString(),map);
    }
    QMap<QString, QList<QMap<QString, QVariant>>> reMap;
    for(const QString &key : Allmap.keys())
    {
        reMap.insert(key, Allmap.values(key));
    }
    QByteArray byte;
    QDataStream Data(&byte,QIODevice::WriteOnly);
    Data << reMap;
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
