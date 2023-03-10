#include "dishwidget.h"
#include "ui_dishwidget.h"
#include "dishesedict.h"
#include "stylesheet.h"
DishWidget::DishWidget(QWidget *parent, QMap<QString, QVariant> data) :
    QWidget(parent),
    ui(new Ui::DishWidget)
{
    ui->setupUi(this);
    ui->checkBox->hide();
    this->setStyleSheet(StyleSheet::labelStyle(1));
    ui->pushButton->setStyleSheet(StyleSheet::buttonStyle(1));
    m_imageW = new DishesEdict(nullptr, data.value("image").toByteArray());
    QString name = QString(data.value("name").toByteArray());
    setClass(QString(data.value("class").toByteArray()));
    setName(name);
    setPrice(data.value("price").toDouble());
    setStorage(data.value("storage").toString());
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

void DishWidget::setStorage(const QString &storage)
{
    if(storage == "yes")
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
    m_imageW->show();
}

