#include "administratorinterface.h"
#include "common.h"
#include "dishinfowidget.h"
#include "orderlist.h"
#include "ui_administratorinterface.h"
#include "adddialog.h"
#include "dishwidget.h"
#include "getneworder.h"
#include "titalwidget.h"
#include "stylesheet.h"
#include "listwidget.h"
#include "tabwidget.h"
#include "classinfowidget.h"
#include "setcostdialog.h"
#include "reportwidget.h"
using namespace Common;
AdministratorInterface::AdministratorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorInterface),
    m_classTab(new TabWidget),
    m_orderTab(new TabWidget),
    m_newOrderList(new ListWidget(2)),
    m_finishOrderList(new ListWidget(2)),
    m_settledOrderList(new ListWidget(2)),
    m_queryOrder(new ListWidget(2)),
    m_report(new ReportWidget)
{
    ui->setupUi(this);
    this->resize(QSize(1400,800));
    ui->horizontalLayout_1->insertWidget(1, m_orderTab);
    m_orderTab->addTab(ui->pushButton_noFinished, m_newOrderList, "No finished");
    m_orderTab->addTab(ui->pushButton_finished, m_finishOrderList, "finished");
    m_orderTab->addTab(ui->pushButton_settled, m_settledOrderList, "Settled");
    connectComBox();
    updateOrderList();
//    ui->checkBox->hide();
    initStyle();
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("餐厅点餐系统服务端"));
    ui->verticalLayout->insertWidget(0,tital);
    ui->verticalLayout_2->insertWidget(1, m_report);
    ui->verticalLayout_3->insertWidget(0, m_queryOrder);
    updateClassList();
    ui->tabWidget->tabBar()->hide();
    connect(ui->pushButton_batchDel,&QPushButton::clicked,this,[this]{
        m_allDishList->showTopCheckBox();
        ui->pushButton_batchDel->setEnabled(false);
        ui->pushButton_finish->setEnabled(true);
    });
    connect(ui->pushButton_finish,&QPushButton::clicked,this,[this]{
        m_allDishList->hideTopCheckBox();
        ui->pushButton_batchDel->setEnabled(true);
        ui->pushButton_finish->setEnabled(false);
        if(m_delList.empty())
        {
            return;
        }
        Service->rep()->delDishes(m_delList);
        updateClassList();
    });
    GetNewOrder *newOrder = new GetNewOrder;
    connect(newOrder, &GetNewOrder::hasNewOrder, this, &AdministratorInterface::hasNewOrder);
    updateReport();
}

AdministratorInterface::~AdministratorInterface()
{
    delete ui;
}

void AdministratorInterface::connectComBox()
{
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    connect(ui->comboBox_query, QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        m_reportMode = index;
        ui->dateEdit->setDateTime(QDateTime::currentDateTime());
        if(index == 0)
        {
            ui->dateEdit->setEnabled(false);
            ui->dateEdit->setDisplayFormat("");
        }
        else if(index == 1)
        {
            ui->dateEdit->setEnabled(true);
            ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
        }
        else
        {
            ui->dateEdit->setEnabled(true);
            ui->dateEdit->setDisplayFormat("yyyy-MM");
        }
    });

}

void AdministratorInterface::updateDishesList()
{
    m_allDishList->clear();
    QMap<QString, QList<Dish>> data= Service->getData();
    for(const QList<Dish> &list : data.values())
    {
        for(const Dish  &dishInfo : list)
        {
            m_priceMap.insert(dishInfo.name, dishInfo.price);
            DishWidget *dish = new DishWidget(this, dishInfo);
            m_allDishList->addWidget(dish);
            m_dishWidgetList.append(dish);
            connect(ui->pushButton_batchDel,&QPushButton::clicked,dish,&DishWidget::showCheckBox);
            connect(ui->pushButton_finish,&QPushButton::clicked,dish,&DishWidget::hideCheckBox);
            connect(dish,&DishWidget::checkBoxStateChanged,this,&AdministratorInterface::setDelList);
        }

    }
}

void AdministratorInterface::updateClassList()
{
    m_classTab->clear();
    m_allDishList = new ListWidget(1);

    for(QPushButton * classButton : qAsConst(m_classButtonList))
    {
        ui->verticalLayout_6->removeWidget(classButton);
        classButton->deleteLater();
    }
    m_classButtonList.clear();
    ui->horizontalLayout_5->insertWidget(2,m_classTab);
    m_classTab->addTab(ui->pushButton_allDish,m_allDishList, "all");
    QMap<QString, QList<Dish>> data= Service->getData();
    m_classList.clear();
    m_classList = Service->classes();
    for(const QString &key : qAsConst(m_classList))
    {
        QPushButton * classButton= new QPushButton(key);
        m_classButtonList.append(classButton);
        ui->verticalLayout_6->insertWidget(ui->verticalLayout_6->count()-1,classButton);
        ListWidget *list = new ListWidget(1);
        for(const Dish &dishMap : data.value(key))
        {
            DishWidget *dish = new DishWidget(this, dishMap);
            list->addWidget(dish);
            connect(ui->pushButton_batchDel,&QPushButton::clicked,dish,&DishWidget::showCheckBox);
            connect(ui->pushButton_finish,&QPushButton::clicked,dish,&DishWidget::hideCheckBox);
            connect(dish,&DishWidget::checkBoxStateChanged,this,&AdministratorInterface::setDelList);
        }
        m_classTab->addTab(classButton,list,key);
    }
    updateDishesList();
}

void AdministratorInterface::updateOrderList()
{
    m_newOrderList->clear();
    m_finishOrderList->clear();
    m_settledOrderList->clear();
    m_queryOrder->clear();
    QList<Order> orderList = Service->getOrder();
    for(const Order &order : orderList)
    {
        OrderList *orderWidget1 = new OrderList(order);
        connect(orderWidget1, &OrderList::updateOrder, this ,&AdministratorInterface::updateOrderList);
        connect(orderWidget1, &OrderList::updateReport, this ,&AdministratorInterface::updateReport);
        OrderList *orderWidget2 = new OrderList(order);
        connect(orderWidget2, &OrderList::updateOrder, this ,&AdministratorInterface::updateOrderList);
        connect(orderWidget2, &OrderList::updateReport, this ,&AdministratorInterface::updateReport);
        m_queryOrder->addWidget(orderWidget2);
        if(order.state == 0)
        {
            m_newOrderList->addWidget(orderWidget1);
        }
        else if(order.state == 1)
        {
            m_finishOrderList->addWidget(orderWidget1);
        }
        else
        {
            m_settledOrderList->addWidget(orderWidget1);
        }
    }
}

void AdministratorInterface::updateReport()
{
    QList<Report> reportList = Service->getDailyReport();
    m_report->initReport(reportList);
}

void AdministratorInterface::on_pushButton_addDishes_clicked()
{
    DishInfoWidget *infoWidget = new DishInfoWidget();
    AddDialog *dialog = new AddDialog;
    dialog->addWidget(infoWidget);
    connect(infoWidget, &DishInfoWidget::infoChanged, dialog, &AddDialog::dishInfoChanged);
    if(QDialog::Accepted == dialog->exec())
    {
        Service->rep()->addDishes(infoWidget->info());
        updateClassList();
    }
}

void AdministratorInterface::on_pushButton_addClass_clicked()
{
    ClassInfoWidget *infoWidget = new ClassInfoWidget;
    AddDialog *dialog = new AddDialog;
    dialog->addWidget(infoWidget);
    connect(infoWidget, &ClassInfoWidget::infoChanged, dialog, &AddDialog::classInfoChanged);
    if(QDialog::Accepted == dialog->exec())
    {
        Service->rep()->addClass(infoWidget->info());
        updateClassList();
    }
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
    int seat;
    QMap<QString, int> dishesMap;

    QDataStream data(&order, QIODevice::OpenModeFlag::ReadOnly);
    data>>seat>>dishesMap;

    QByteArray orderByte;
    QDataStream dishes(&orderByte, QIODevice::OpenModeFlag::WriteOnly);
    dishes << dishesMap;
    QMap<QString, QByteArray> orderMap;
    orderMap.insert("seat", QString::number(seat).toUtf8());
    orderMap.insert("total", QString::number(Common::calculateTotal(m_priceMap, dishesMap)).toUtf8());
    orderMap.insert("dishes", orderByte);
    orderMap.insert("state", QString::number(0).toUtf8());
    Service->rep()->addOrder(orderMap);
    updateOrderList();
}

void AdministratorInterface::on_pushButton_orderManage_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void AdministratorInterface::on_pushButton_dishManage_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void AdministratorInterface::on_pushButton_history_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void AdministratorInterface::on_pushButton_report_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void AdministratorInterface::initStyle()
{
    ui->pushButton_orderManage->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_dishManage->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_history->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_report->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_modClass->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_addDishes->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_addClass->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_delClass->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_batchDel->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_finish->setStyleSheet(StyleSheet::buttonStyle());
    ui->lineEdit->setStyleSheet(StyleSheet::lineEditStyle());
    ui->pushButton_query->setStyleSheet(StyleSheet::buttonStyle());
//    ui->widget_head2->setStyleSheet(StyleSheet::labelStyle());
}
#include "orderlist.h"
void AdministratorInterface::on_pushButton_query_clicked()
{

}

void AdministratorInterface::on_pushButton_clicked()
{
    SetCostDialog dialog;
    if(QDialog::Accepted == dialog.exec())
    {
        QPair<QString, double> info = dialog.getInfo();
        ConnectService::service()->rep()->setDailyCost(info.first, info.second);
    }
}

void AdministratorInterface::on_pushButton_queryR_clicked()
{
    QList<Report> reportList;
    if(m_reportMode == 0)
    {
        reportList = Service->getDailyReport();
    }
    else if(m_reportMode == 1)
    {
        reportList = Service->getDailyReport(ui->dateEdit->date().toString("yyyy-MM-dd"));
    }
    else
    {
        reportList = Service->getMonthlyReport(ui->dateEdit->date().toString("yyyy-MM"));
    }
    m_report->initReport(reportList);
}
