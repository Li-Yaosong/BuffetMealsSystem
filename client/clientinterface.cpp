#include "clientinterface.h"
#include "ui_clientinterface.h"
#include "cdishwidget.h"
#include "connectservice.h"
#include "common.h"
#include "placeorder.h"
ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);
    m_service = new ConnectService();
    updateDishesList();
    connect(ui->pushButton_allClean, &QPushButton::clicked, this, &ClientInterface::allclean);
    PlaceOrder *placeOrder = new PlaceOrder("127.0.0.1", 8888);
    placeOrder->orderInfo("hello");

}

ClientInterface::~ClientInterface()
{
    delete ui;
}

void ClientInterface::updateDishesList()
{
    if(!m_dishWidgetList.empty())
    {
        for(CDishWidget *dish : qAsConst(m_dishWidgetList))
        {
            ui->gridLayout->removeWidget(dish);
            dish->deleteLater();
        }
        m_dishWidgetList.clear();
    }
    QMap<int, QMap<QString, QVariant>> data= m_service->getData();
    QList<int> keys =  data.keys();
    for(int key : keys)
    {
        CDishWidget *dish = new CDishWidget(this, Common::mapToDish(data.value(key)));
        //连接全部清除按钮
        connect(this, &ClientInterface::allclean, dish, &CDishWidget::reSetNumber);
        ui->gridLayout->addWidget(dish,key/3,key%3);
        m_dishWidgetList.append(dish);
    }
}
