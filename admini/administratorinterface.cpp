#include "administratorinterface.h"
#include "dishinfowidget.h"
#include "orderlist.h"
#include "ui_administratorinterface.h"
#include "adddialog.h"
#include "dishwidget.h"
#include "getneworder.h"
#include "titalwidget.h"
#include "stylesheet.h"
#include "dishlistwidget.h"
#include "classtabwidget.h"
#include "classinfowidget.h"
AdministratorInterface::AdministratorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorInterface),
    m_classTab(new ClassTabWidget)
{
    ui->setupUi(this);
    this->resize(QSize(1400,800));
//    ui->checkBox->hide();
    initStyle();
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("餐厅点餐系统服务端"));
    ui->verticalLayout->insertWidget(0,tital);
    m_service = new ConnectService;
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
        m_service->delDishes(m_delList);
        updateClassList();
    });
    GetNewOrder *newOrder = new GetNewOrder;
    connect(newOrder, &GetNewOrder::hasNewOrder, this, &AdministratorInterface::hasNewOrder);
}

AdministratorInterface::~AdministratorInterface()
{
    delete ui;
}

void AdministratorInterface::updateDishesList()
{
    m_allDishList->clear();
    QMap<QString, QList<QMap<QString, QVariant>>> data= m_service->getData();
    for(const QList<QMap<QString, QVariant>> &list : data.values())
    {
        for(const QMap<QString, QVariant> &map : list)
        {
            DishWidget *dish = new DishWidget(this, map);
            m_allDishList->addDishWidget(dish);
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
    m_allDishList = new DishListWidget;

    for(QPushButton * classButton : qAsConst(m_classButtonList))
    {
        ui->verticalLayout_6->removeWidget(classButton);
        classButton->deleteLater();
    }
    m_classButtonList.clear();
    ui->horizontalLayout_5->insertWidget(2,m_classTab);
    m_classTab->addTab(ui->pushButton_allDish,m_allDishList, "all");
    QMap<QString, QVariant> classData= m_service->getClass();
    QMap<QString, QList<QMap<QString, QVariant>>> data= m_service->getData();
    m_classList.clear();
    m_classList = classData.keys();
    for(const QString &key : qAsConst(m_classList))
    {
        QPushButton * classButton= new QPushButton(key);
        m_classButtonList.append(classButton);
        ui->verticalLayout_6->insertWidget(ui->verticalLayout_6->count()-1,classButton);
        DishListWidget *list = new DishListWidget();
        for(const QMap<QString, QVariant> &dishMap : data.value(key))
        {
            DishWidget *dish = new DishWidget(this, dishMap);
            list->addDishWidget(dish);
            connect(ui->pushButton_batchDel,&QPushButton::clicked,dish,&DishWidget::showCheckBox);
            connect(ui->pushButton_finish,&QPushButton::clicked,dish,&DishWidget::hideCheckBox);
            connect(dish,&DishWidget::checkBoxStateChanged,this,&AdministratorInterface::setDelList);
        }
        m_classTab->addTab(classButton,list,key);
    }
    updateDishesList();
}

void AdministratorInterface::on_noFinished_pushButton_clicked()
{
    OrderList *order = new OrderList();
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count() - 1,order);
}


void AdministratorInterface::on_pushButton_addDishes_clicked()
{
    DishInfoWidget *infoWidget = new DishInfoWidget(m_classList);
    AddDialog *dialog = new AddDialog;
    dialog->addWidget(infoWidget);
    connect(infoWidget, &DishInfoWidget::infoChanged, dialog, &AddDialog::setOkButtonState);
    if(QDialog::Accepted == dialog->exec())
    {
        QMap<QString, QByteArray> map = infoWidget->info();
        map.insert("storage", "yes");
        m_service->addDishes(map);
        updateClassList();
    }
}

void AdministratorInterface::on_pushButton_addClass_clicked()
{
    ClassInfoWidget *infoWidget = new ClassInfoWidget;
    AddDialog *dialog = new AddDialog;
    dialog->addWidget(infoWidget);
    connect(infoWidget, &ClassInfoWidget::infoChanged, dialog, &AddDialog::setOkButtonState);
    if(QDialog::Accepted == dialog->exec())
    {
        QMap<QString, QByteArray> map = infoWidget->info();
        m_service->addClass(map);
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
    QStringList list = dishesMap.keys();
    QDateTime dateTime(QDateTime::currentDateTime());
    ui->textEdit->append(QString::fromLocal8Bit("座位号: ") + QString::number(seat));
    ui->textEdit->append(QString::fromLocal8Bit("时间: ") +dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->textEdit->append(QString::fromLocal8Bit("所点菜单如下: "));
    for(const QString &dish : list)
    {
        ui->textEdit->append(dish+"  "+QString::number(dishesMap.value(dish))+QString::fromLocal8Bit("份"));
    }
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


void AdministratorInterface::on_pushButton_test_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void AdministratorInterface::initStyle()
{
    ui->pushButton_orderManage->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_dishManage->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_history->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_test->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_4->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_addDishes->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_addClass->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_delClass->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_batchDel->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_finish->setStyleSheet(StyleSheet::buttonStyle());
    ui->lineEdit->setStyleSheet(StyleSheet::lineEditStyle());
    ui->pushButton_query->setStyleSheet(StyleSheet::buttonStyle());
//    ui->widget_head2->setStyleSheet(StyleSheet::labelStyle());
}
