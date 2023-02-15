#include "clientinterface.h"
#include "ui_clientinterface.h"
#include "cdishwidget.h"
#include "connectservice.h"
#include "common.h"
ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);
    m_service = new ConnectService();
    updateDishesList();
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
        ui->gridLayout->addWidget(dish,key/3,key%3);
        m_dishWidgetList.append(dish);
    }
}

void ClientInterface::on_pushButton_clicked()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            CDishWidget *oder = new CDishWidget;
            ui->gridLayout->addWidget(oder,i,j);
        }
    }

}

