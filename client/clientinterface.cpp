#include "clientinterface.h"
#include "tabwidget.h"
#include "listwidget.h"
#include "ui_clientinterface.h"
#include "cdishwidget.h"
#include "connectservice.h"
#include "common.h"
#include "placeorder.h"
#include "titalwidget.h"
#include "orderconfirmatdialog.h"
#include "stylesheet.h"
#include "classbutton.h"

#include<QScrollBar>
ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface),
    m_classTab(new TabWidget)
{
    ui->setupUi(this);
    resize(1770, 1100);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("餐厅点餐系统客户端"));
    ui->verticalLayout->insertWidget(0, tital);
    connect(ui->pushButton_allClean, &QPushButton::clicked, this, &ClientInterface::allclean);
    m_placeOrder = new PlaceOrder("127.0.0.1", 8888);

    m_allClassButton = new ClassButton(QStringLiteral("全部"), QIcon(":/image/all.png"));
    ui->verticalLayout_2->insertWidget(0, m_allClassButton);
    initStyle();
    ui->pushButton_setSeatNum->setText(QStringLiteral("设置座位号"));
    updateClassList();
}

ClientInterface::~ClientInterface()
{
    delete ui;
}

void ClientInterface::updateDishesList()
{
    m_allDishList->clear();
    QMap<QString, QList<Dish>> data= Service->getData();
    for(const QList<Dish> &list : data.values())
    {
        for(const Dish &dishInfo : list)
        {
            if(dishInfo.storage > 0)
            {
                CDishWidget *dish = new CDishWidget(this, dishInfo);
                dish->createBind(m_dishWidgetMap.value(dishInfo.name));
                //连接全部清除按钮
                connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
                connect(dish, &CDishWidget::dataChange, this, &ClientInterface::addDishes);
                m_allDishList->addWidget(dish);
                m_dishWidgetList.append(dish);
            }
        }

    }
}

void ClientInterface::addDishes(QPair<QString, int> dish)
{
    if(dish.second == 0 && m_orderMap.contains(dish.first))
    {
        m_orderMap.remove(dish.first);
    }
    if(dish.second != 0)
    {
        m_orderMap.insert(dish.first, dish.second);
    }
}

void ClientInterface::updateClassList()
{
    m_classTab->clear();
    m_allDishList = new ListWidget(0);
    m_classTab->addTab(m_allClassButton->button(),m_allDishList, "all");
    m_dishWidgetMap.clear();
    for(ClassButton * classButton : qAsConst(m_classButtonList))
    {
        ui->verticalLayout_2->removeWidget(classButton);
        classButton->deleteLater();
    }
    m_classButtonList.clear();
    ui->horizontalLayout->insertWidget(1,m_classTab);

    QMap<QString, QVariant> classData= Service->getClass();
    QMap<QString, QList<Dish>> data= Service->getData();
    m_classList.clear();
    m_classList = classData.keys();
    for(const QString &key : qAsConst(m_classList))
    {
        QPixmap pixmap;
        pixmap.loadFromData(classData.value(key).toByteArray());
        ClassButton *classButton= new ClassButton(key, QIcon(pixmap));
//        QPushButton * classButton= new QPushButton(key);
        m_classButtonList.append(classButton);
        ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-1,classButton);
        ListWidget *list = new ListWidget(0);
        for(const Dish &dishInfo : data.value(key))
        {
            if(dishInfo.storage > 0)
            {
                CDishWidget *dish = new CDishWidget(this, dishInfo);
                connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
                connect(dish, &CDishWidget::dataChange, this, &ClientInterface::addDishes);
                list->addWidget(dish);
                m_dishWidgetMap.insert(dishInfo.name,dish);
            }
        }
        m_classTab->addTab(classButton->button(),list,key);
    }
    updateDishesList();
}

void ClientInterface::initStyle()
{
    ui->scrollArea->verticalScrollBar()->setStyleSheet(StyleSheet::scrollBarStyle());
    ui->spinBox->setStyleSheet(StyleSheet::spinBoxStyle());
    ui->label->setStyleSheet(StyleSheet::labelStyle(0));
    ui->pushButton_setSeatNum->setStyleSheet(StyleSheet::buttonStyle(1));
    ui->pushButton_refresh->setStyleSheet(StyleSheet::buttonStyle(5));
    ui->pushButton_refresh->setIcon(QIcon(":/image/refresh.png"));
    int h = ui->pushButton_refresh->height();
    ui->pushButton_refresh->setIconSize(QSize(h, h));
}

void ClientInterface::on_pushButton_placeOrder_clicked()
{
    if(!m_orderMap.empty())
    {
        OrderConfirmatDialog *dialog = new OrderConfirmatDialog(m_orderMap);
        if(QDialog::Accepted == dialog->exec())
        {
            QByteArray byte;
            QDataStream input(&byte, QIODevice::OpenModeFlag::WriteOnly);
            input<<m_seat<<m_orderMap;
            m_placeOrder->orderInfo(byte);
        }
    }
}


void ClientInterface::on_pushButton_setSeatNum_clicked()
{
    QString text = ui->pushButton_setSeatNum->text();
    if( text == QStringLiteral("设置座位号"))
    {
        ui->pushButton_setSeatNum->setText(QStringLiteral("完成"));
        ui->spinBox->setEnabled(true);
        ui->spinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
    }
    else if(text == QStringLiteral("完成"))
    {
        ui->pushButton_setSeatNum->hide();
        ui->spinBox->setEnabled(false);
        ui->spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_seat = ui->spinBox->value();
        qDebug()<<QStringLiteral("座位号为：")<<QString::number(m_seat) << QStringLiteral("号");
    }
}


void ClientInterface::on_pushButton_refresh_clicked()
{
    updateClassList();
}

