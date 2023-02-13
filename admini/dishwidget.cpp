#include "dishwidget.h"
#include "ui_dishwidget.h"

DishWidget::DishWidget(QWidget *parent, QMap<QString, QVariant> data) :
    QWidget(parent),
    ui(new Ui::DishWidget)
{
    ui->setupUi(this);
    m_imageW = new ImageDialog(this,data.value("image").toByteArray());
    QString name = QString(data.value("name").toByteArray());
    setNum(QString(data.value("number").toByteArray()));
    setName(name);
    setPrice(data.value("price").toDouble());
    setStorage(data.value("storage").toString());

}

DishWidget::~DishWidget()
{
    delete ui;
}

void DishWidget::setNum(const QString &num)
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
        ui->label_storage->setText(QString::fromLocal8Bit("enough"));
    }
    else
    {
        ui->label_storage->setText(QString::fromLocal8Bit("Not enough"));
    }
}

void DishWidget::on_pushButton_clicked()
{
    m_imageW->exec();
}

