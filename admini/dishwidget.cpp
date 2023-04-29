#include "dishwidget.h"
#include "dishesedict.h"
#include "ui_dishwidget.h"
//#include "dishesedict.h"
#include "stylesheet.h"
DishWidget::DishWidget(QWidget *parent, Dish dishInfo) :
    QWidget(parent),
    ui(new Ui::DishWidget),
    m_dishInfo(dishInfo)
{
    ui->setupUi(this);
    ui->checkBox->hide();
    this->setStyleSheet(StyleSheet::labelStyle(1));
    ui->pushButton->setStyleSheet(StyleSheet::buttonStyle(1));
    setClass(m_dishInfo.className);
    setName(m_dishInfo.name);
    setPrice(m_dishInfo.price);
    setStorage(m_dishInfo.storage);
    connect(ui->checkBox, &QCheckBox::stateChanged,this, [this]{
        if(ui->checkBox->isCheckable())
        {
            emit checkBoxStateChanged(ui->label_name->text(),true);
        }
        else
        {
            emit checkBoxStateChanged(ui->label_name->text(),false);
        }
    });
}

DishWidget::~DishWidget()
{
    delete ui;
}

void DishWidget::setClass(const QString &num)
{
    ui->label_num->setText(num);
}

void DishWidget::setName(const QString &name)
{
    ui->label_name->setText(name);
}

void DishWidget::setPrice(const double &price)
{
    ui->label_price->setText(QString::number(price));
}

void DishWidget::setStorage(const int &storage)
{
    if(storage)
    {
        ui->label_storage->setText(QString::fromLocal8Bit("充足"));
        ui->label_storage->setStyleSheet(StyleSheet::labelStyle(2));
    }
    else
    {
        ui->label_storage->setText(QString::fromLocal8Bit("不足"));
        ui->label_storage->setStyleSheet(StyleSheet::labelStyle(3));
    }
}

void DishWidget::showCheckBox()
{
    ui->checkBox->show();
}

void DishWidget::hideCheckBox()
{
    ui->checkBox->hide();
}

void DishWidget::on_pushButton_clicked()
{

    m_imageW = new DishesEdict(m_dishInfo);
    m_imageW->show();
}

