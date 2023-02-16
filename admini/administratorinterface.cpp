#include "administratorinterface.h"
#include "orderlist.h"
#include "ui_administratorinterface.h"
#include "adddishesdialog.h"
#include "dishwidget.h"
#include "getneworder.h"
AdministratorInterface::AdministratorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorInterface)
{

    ui->setupUi(this);
    ui->checkBox->hide();
    m_service = new ConnectService;

    connect(ui->pushButton_batchDel,&QPushButton::clicked,this,[this]{
        ui->checkBox->show();
//        m_service->delDishes();
        ui->pushButton_batchDel->setEnabled(false);
        ui->pushButton_finish->setEnabled(true);
    });
    connect(ui->pushButton_finish,&QPushButton::clicked,this,[this]{
        ui->checkBox->hide();
        ui->pushButton_batchDel->setEnabled(true);
        ui->pushButton_finish->setEnabled(false);
        m_service->delDishes(m_delList);
        updateDishesList();
    });
    GetNewOrder *newOrder = new GetNewOrder;
    connect(newOrder, &GetNewOrder::hasNewOrder, this, &AdministratorInterface::hasNewOrder);
    updateDishesList();

}

AdministratorInterface::~AdministratorInterface()
{
    delete ui;
}

void AdministratorInterface::updateDishesList()
{
    if(!m_dishWidgetList.empty())
    {
        for(DishWidget *dish : qAsConst(m_dishWidgetList))
        {
            ui->verticalLayout_5->removeWidget(dish);
            dish->deleteLater();
        }
        m_dishWidgetList.clear();
    }
    QMap<int, QMap<QString, QVariant>> data= m_service->getData();
    QList<int> keys =  data.keys();
    for(int key : keys)
    {
        DishWidget *dish = new DishWidget(this, data.value(key));
        m_dishWidgetList.append(dish);
        ui->verticalLayout_5->insertWidget(ui->verticalLayout_5->count()- 1,dish);
        connect(ui->pushButton_batchDel,&QPushButton::clicked,dish,&DishWidget::showCheckBox);
        connect(ui->pushButton_finish,&QPushButton::clicked,dish,&DishWidget::hideCheckBox);
        connect(dish,&DishWidget::checkBoxStateChanged,this,&AdministratorInterface::setDelList);
    }
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
        map.insert("number",QString::number(m_dishWidgetList.count()).toUtf8());
        m_service->addDishes(map);
    }
    updateDishesList();
}

void AdministratorInterface::setDelList(QString name, bool del)
{
    if(del)
    {
        if(!m_delList.contains(name))
        {
            m_delList.append(name);
        }
    }
    else
    {
        if(m_delList.contains(name))
        {
            m_delList.removeAll(name);
        }
    }

}

void AdministratorInterface::hasNewOrder(QByteArray order)
{
    ui->lineEdit->setText(order);
}


void AdministratorInterface::on_pushButton_4_clicked()
{
    if(!m_dishWidgetList.empty())
    {
        for(DishWidget *dish : m_dishWidgetList)
        {
            ui->verticalLayout_5->removeWidget(dish);
            dish->deleteLater();
        }
        m_dishWidgetList.clear();
    }
}
