#include "administratorinterface.h"
#include "orderlist.h"
#include "ui_administratorinterface.h"
#include "adddishesdialog.h"
#include "dishwidget.h"
AdministratorInterface::AdministratorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorInterface)
{
    ui->setupUi(this);
    m_service = new ConnectService;
    QMap<int, QMap<QString, QVariant>> data= m_service->getData();
    QList<int> keys =  m_service->getData().keys();
    for(int key : keys)
    {
        DishWidget *dish = new DishWidget(this, data.value(key));
        ui->verticalLayout_5->insertWidget(ui->verticalLayout_5->count()- 1,dish);
    }

}

AdministratorInterface::~AdministratorInterface()
{
    delete ui;
}

void AdministratorInterface::on_noFinished_pushButton_clicked()
{
    OrderList *order = new OrderList();
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count() - 1,order);
}


void AdministratorInterface::on_pushButton_addDishes_clicked()
{
    AddDishesDialog dialog;
    if(QDialog::Accepted == dialog.exec())
    {
        QMap<QString, QByteArray> map = dialog.getInfo();
        m_number++;
        map.insert("number",QString::number(m_number).toUtf8());
        m_service->addDishes(map);
    }
}

