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
ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface),
    m_classTab(new TabWidget)
{
    ui->setupUi(this);
    resize(1620, 1000);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("餐厅点餐系统客户端"));
    ui->verticalLayout->insertWidget(0, tital);
    connect(ui->pushButton_allClean, &QPushButton::clicked, this, &ClientInterface::allclean);
    m_placeOrder = new PlaceOrder("127.0.0.1", 8888);
    updateClassList();
//    connect(ui->pushButton_placeOrder, &QPushButton::clicked, this, &ClientInterface::placeOrder);
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
            if(dishInfo.storage >= 0)
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

void ClientInterface::placeOrder()
{
    QByteArray byte;
    QDataStream input(&byte, QIODevice::OpenModeFlag::WriteOnly);

    if(!m_orderMap.empty())
    {
        input<<m_seat<<m_orderMap;
        m_placeOrder->orderInfo(byte);
    }
}

void ClientInterface::updateClassList()
{
    m_classTab->clear();
    m_allDishList = new ListWidget(0);
    m_dishWidgetMap.clear();
    for(QPushButton * classButton : qAsConst(m_classButtonList))
    {
        ui->verticalLayout_2->removeWidget(classButton);
        classButton->deleteLater();
    }
    m_classButtonList.clear();
    ui->horizontalLayout->insertWidget(1,m_classTab);
    m_classTab->addTab(ui->pushButton_allDish,m_allDishList, "all");
    QMap<QString, QVariant> classData= Service->getClass();
    QMap<QString, QList<Dish>> data= Service->getData();
    m_classList.clear();
    m_classList = classData.keys();
    for(const QString &key : qAsConst(m_classList))
    {
        QPushButton * classButton= new QPushButton(key);
        m_classButtonList.append(classButton);
        ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-1,classButton);
        ListWidget *list = new ListWidget(0);
        for(const Dish &dishInfo : data.value(key))
        {
            if(dishInfo.storage >= 0)
            {
                CDishWidget *dish = new CDishWidget(this, dishInfo);
                connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
                connect(dish, &CDishWidget::dataChange, this, &ClientInterface::addDishes);
                list->addWidget(dish);
                m_dishWidgetMap.insert(dishInfo.name,dish);
            }
        }
        m_classTab->addTab(classButton,list,key);
    }
    updateDishesList();
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

