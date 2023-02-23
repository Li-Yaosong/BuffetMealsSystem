#include "clientinterface.h"
#include "classtabwidget.h"
#include "dishlistwidget.h"
#include "ui_clientinterface.h"
#include "cdishwidget.h"
#include "connectservice.h"
#include "common.h"
#include "placeorder.h"
#include "titalwidget.h"
ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface),
    m_classTab(new ClassTabWidget)
{
    ui->setupUi(this);
    m_service = new ConnectService();
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("餐厅点餐系统客户端"));
    ui->verticalLayout->insertWidget(0, tital);
    connect(ui->pushButton_allClean, &QPushButton::clicked, this, &ClientInterface::allclean);
    m_placeOrder = new PlaceOrder("127.0.0.1", 8888);
    updateClassList();
    connect(ui->pushButton_placeOrder, &QPushButton::clicked, this, &ClientInterface::placeOrder);
}

ClientInterface::~ClientInterface()
{
    delete ui;
}

void ClientInterface::updateDishesList()
{
    m_allDishList->clear();
    QMap<QString, QList<QMap<QString, QVariant>>> data= m_service->getData();
    for(const QList<QMap<QString, QVariant>> &list : data.values())
    {
        for(const QMap<QString, QVariant> &map : list)
        {
            if(map.value("storage").toString() == "yes")
            {
                CDishWidget *dish = new CDishWidget(this, Common::mapToDish(map));
                dish->createBind(m_dishWidgetMap.value(map.value("name").toString()));
                //连接全部清除按钮
                connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
                connect(dish, &CDishWidget::dataChange, this, &ClientInterface::addDishes);
                m_allDishList->addDishWidget(dish);
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
    else
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
    m_allDishList = new DishListWidget(false);
    m_dishWidgetMap.clear();
    for(QPushButton * classButton : qAsConst(m_classButtonList))
    {
        ui->verticalLayout_2->removeWidget(classButton);
        classButton->deleteLater();
    }
    m_classButtonList.clear();
    ui->horizontalLayout->insertWidget(1,m_classTab);
    m_classTab->addTab(ui->pushButton_allDish,m_allDishList, "all");
    QMap<QString, QVariant> classData= m_service->getClass();
    QMap<QString, QList<QMap<QString, QVariant>>> data= m_service->getData();
    m_classList.clear();
    m_classList = classData.keys();
    for(const QString &key : qAsConst(m_classList))
    {
        QPushButton * classButton= new QPushButton(key);
        m_classButtonList.append(classButton);
        ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-1,classButton);
        DishListWidget *list = new DishListWidget(false);
        for(const QMap<QString, QVariant> &dishMap : data.value(key))
        {
            if(dishMap.value("storage").toString() == "yes")
            {
                CDishWidget *dish = new CDishWidget(this, Common::mapToDish(dishMap));
                connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
                connect(dish, &CDishWidget::dataChange, this, &ClientInterface::addDishes);
                list->addDishWidget(dish);
                m_dishWidgetMap.insert(dishMap.value("name").toString(),dish);
            }
        }
        m_classTab->addTab(classButton,list,key);
    }
    updateDishesList();
}
